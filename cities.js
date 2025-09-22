const API_BASE = 'http://localhost:3001';

class CitiesAPI {
    // Get all cities
    async getAllCities() {
        try {
            const response = await fetch(`${API_BASE}/api/cities`);
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            return await response.json();
        } catch (error) {
            throw new Error('Failed to fetch cities: ' + error.message);
        }
    }

     // Get foods for a specific city
    async getCityFood(cityId) {
        try {
            console.log(`Fetching from: ${API_BASE}/api/cities/${cityId}/food`);
            const response = await fetch(`${API_BASE}/api/cities/${cityId}/food`);
            
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            
            const data = await response.json();
            console.log('Raw API response:', data);
            return data;
        } catch (error) {
            console.error('Fetch error details:', error);
            throw new Error('Failed to fetch city food: ' + error.message);
        }
    }
}

// Create a global instance
const citiesAPI = new CitiesAPI();