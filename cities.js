const API_BASE = 'http://localhost:3001';

class CitiesAPI {
    // Get all cities
    async getAllCities() {
        try {
            const response = await fetch(`${API_BASE}/api/cities`);
            return await response.json();
        } catch (error) {
            throw new Error('Failed to fetch cities: ' + error.message);
        }
    }

    // Get all cities with their food
    async getAllCitiesWithFood() {
        try {
            const response = await fetch(`${API_BASE}/api/cities/food`);
            return await response.json();
        } catch (error) {
            throw new Error('Failed to fetch cities with food: ' + error.message);
        }
    }

    // Get foods for a specific city
    async getCityFood(cityId) {
        try {
            const response = await fetch(`${API_BASE}/api/cities/${cityId}/food`);
            return await response.json();
        } catch (error) {
            throw new Error('Failed to fetch city food: ' + error.message);
        }
    }

    // Check API health
    async checkHealth() {
        try {
            const response = await fetch(`${API_BASE}/health`);
            return await response.text();
        } catch (error) {
            throw new Error('API is not running: ' + error.message);
        }
    }
}

// Create a global instance
const citiesAPI = new CitiesAPI();