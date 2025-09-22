// Mock data for cities and foods
const cities = [
  { id: 1, name: 'New York' },
  { id: 2, name: 'London' },
  { id: 3, name: 'Tokyo' }
];

const foods = [
  { id: 1, cityId: 1, name: 'Pizza', price: 10 },
  { id: 2, cityId: 1, name: 'Bagel', price: 5 },
  { id: 3, cityId: 2, name: 'Fish & Chips', price: 12 },
  { id: 4, cityId: 2, name: 'Tea', price: 3 },
  { id: 5, cityId: 3, name: 'Sushi', price: 15 },
  { id: 6, cityId: 3, name: 'Ramen', price: 8 }
];

module.exports = { cities, foods };