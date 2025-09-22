// Simple Express backend for City Food API
const express = require('express');
const cors = require('cors');
const { cities, foods } = require('./mockData');

const app = express();
const PORT = 3001;

app.use(cors());
app.use(express.json());

// Health check
app.get('/health', (req, res) => {
  res.send('API is running');
});

// Get all cities
app.get('/api/cities', (req, res) => {
  res.json({ cities });
});

// Get all cities with their foods
app.get('/api/cities/food', (req, res) => {
  const citiesWithFood = cities.map(city => ({
    ...city,
    food: foods.filter(food => food.cityId === city.id)
  }));
  res.json({ cities: citiesWithFood });
});

// Get foods for a specific city
app.get('/api/cities/:id/food', (req, res) => {
  const cityId = parseInt(req.params.id);
  const city = cities.find(c => c.id === cityId);
  if (!city) {
    return res.status(404).json({ error: 'City not found' });
  }
  const cityFood = foods.filter(food => food.cityId === cityId);
  res.json({ city: city.name, food: cityFood });
});

app.listen(PORT, () => {
  console.log(`API server running on http://localhost:${PORT}`);
});

