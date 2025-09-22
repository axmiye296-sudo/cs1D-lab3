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
            // Create city name
            const cityBtn = document.createElement('span');
            cityBtn.textContent = city.name;
            cityBtn.style.display = 'block';
            cityBtn.style.flex = '1';

            // Arrow icon
            const arrow = document.createElement('i');
            arrow.className = 'fa-solid fa-chevron-down';
            arrow.style.marginRight = '8px';
            arrow.style.transition = 'transform 0.2s';

            // Container for city name and arrow
            const cityRow = document.createElement('button');
            cityRow.style.display = 'flex';
            cityRow.appendChild(arrow);
            cityRow.appendChild(cityBtn);

            // Collapsible content div (hidden by default)
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
                    arrow.className = 'fa-solid fa-chevron-up';
                } else {
                    foodDiv.style.display = 'none';
                    arrow.className = 'fa-solid fa-chevron-down';
                }
            };

            container.appendChild(cityRow);
            container.appendChild(foodDiv);
        });
    } catch (error) {
        console.error('API connection failed:', error);
        alert('Cannot connect to API. Make sure the server is running on http://localhost:3001');
    }
};