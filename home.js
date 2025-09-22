// UI functions that use the CitiesAPI class

// Check API health on page load
window.onload = async function() {
    try {
        await citiesAPI.checkHealth();
        console.log('API is running');

        // Fetch all cities with their foods
        const data = await citiesAPI.getAllCitiesWithFood();

        const container = document.getElementById('cities-result');
        container.innerHTML = '';

        data.cities.forEach(city => {
        // Create city name button
        const cityBtn = document.createElement('button');
        cityBtn.textContent = city.name;
        cityBtn.style.display = 'block';
        cityBtn.style.margin = '8px 0';

        // Create collapsible content div (hidden by default)
        const foodDiv = document.createElement('div');
        foodDiv.style.display = 'none';
        foodDiv.style.marginLeft = '20px';

        cityBtn.onclick = async () => {
            if (foodDiv.style.display === 'none') {
            const foodData = await citiesAPI.getCityFood(city.id);
            foodDiv.innerHTML = foodData.food.length
                ? foodData.food.map(f => `<div>${f.name} - $${f.price}</div>`).join('')
                : '<div>No foods found</div>';
            foodDiv.style.display = 'block';
            } else {
            foodDiv.style.display = 'none';
            }
        };

        container.appendChild(cityBtn);
        container.appendChild(foodDiv);
        });
    } catch (error) {
        console.error('API connection failed:', error);
        alert('Cannot connect to API. Make sure the server is running on http://localhost:3001');
    }
};