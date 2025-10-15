# Admin File Upload Functionality

## Overview
The admin file upload functionality allows authenticated administrators to upload city data files that contain comprehensive information about cities including food items and distances to other cities. The system supports both JSON format (for multiple cities) and legacy text format (for single city).

## API Endpoint

### POST /api/admin/upload-city

**Authentication Required:** Yes (Admin login required)

**Content-Type:** multipart/form-data

**Parameters:**
- `cityData` (file): A JSON file (recommended) or text file containing city information

**Response:**
- `201 Created`: File processed successfully
- `400 Bad Request`: Invalid file or missing data
- `403 Forbidden`: Authentication required
- `500 Internal Server Error`: Processing failed

## File Formats

### JSON Format (Recommended - Multiple Cities)

The system automatically detects JSON format and can process multiple cities in a single upload:

```json
{
  "cities": [
    {
      "name": "Tokyo",
      "foods": [
        {"name": "Sushi", "price": 25.50},
        {"name": "Ramen", "price": 12.00}
      ],
      "distances": [
        {"to": "London", "distance": 9500},
        {"to": "Paris", "distance": 9700}
      ]
    },
    {
      "name": "Sydney", 
      "foods": [
        {"name": "Meat Pie", "price": 8.50}
      ],
      "distances": [
        {"to": "Tokyo", "distance": 7800}
      ]
    }
  ]
}
```

### Text Format (Legacy - Single City)

The original text format is still supported for backward compatibility:

```
CITY: [City Name]

FOODS:
[Food Name],[Price]
[Food Name],[Price]
...

DISTANCES:
[Destination City],[Distance in km]
[Destination City],[Distance in km]
...
```

### Example File Content:

```
CITY: Tokyo

FOODS:
Sushi,25.50
Ramen,12.00
Tempura,18.75
Yakitori,15.30

DISTANCES:
London,9500
Paris,9700
Berlin,8900
Madrid,11200
Rome,10100
```

## Implementation Details

### AdminService Methods

1. **`processCitiesJsonFile(const std::string& jsonContent)`**
   - Parses JSON files with multiple cities
   - Validates JSON structure and data types
   - Processes each city individually
   - Returns boolean indicating overall success

2. **`processCityDataFile(const std::string& fileContent)`**
   - Parses legacy text format (single city)
   - Extracts city name, foods, and distances
   - Returns boolean indicating success

3. **`addCityFromFileData(cityName, foods, distances)`**
   - Creates new city in database
   - Adds all food items for the city
   - Saves distance relationships to other cities

### Format Detection

The system automatically detects file format:
- **JSON**: Files starting with `{` or `[`
- **Text**: All other files (legacy format)

### Batch Processing

JSON format allows processing multiple cities in a single request:
- Each city is processed independently
- Partial success is reported (e.g., "3/5 cities processed successfully")
- Individual city failures don't stop processing of remaining cities

### Database Operations

- **Cities**: Added to `cities` table
- **Foods**: Added to `foods` table with city association
- **Distances**: Added to `city_distances` table (bidirectional relationships)

### Error Handling

- File format validation
- City name uniqueness checking
- Database transaction safety
- Destination city existence verification for distances

## Testing

Use the provided test scripts:

1. **Python Test Script**: `test_upload.py`
   - Requires `requests` library
   - Tests both JSON and text formats
   - Automatically detects available test files

2. **Bash Test Script**: `test_upload.sh`
   - Uses curl commands
   - Tries JSON format first, falls back to text
   - Suitable for command-line testing

3. **Sample Data**: 
   - `sample_cities_data.json` - Multiple cities in JSON format (recommended)
   - `sample_city_data.txt` - Single city in text format (legacy)

## Usage Examples

### Multiple Cities (JSON)
1. Create a JSON file with multiple cities
2. Upload via `/api/admin/upload-city`
3. System processes all cities in batch
4. Returns success count and details

### Single City (Text - Legacy)
1. Create a text file with single city data
2. Upload via same endpoint
3. System auto-detects format and processes accordingly

## Dependencies

- Crow framework (multipart/form-data support)
- CityRepository, FoodRepository, CityDistanceRepository
- SQLite database with proper schema

## Security Considerations

- Admin authentication required for all operations
- File content validation prevents malicious input
- Database transaction safety ensures data integrity
- Error messages don't expose sensitive information