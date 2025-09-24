// UI functions that use the CitiesAPI class

// Check API health on page load
// first thing to run when the page loads, allows backend to be displayed right away
window.onload = async function() {
    try {
        await citiesAPI.checkHealth();
        console.log('API is running');

        // Fetch all cities with their foods
        const data = await citiesAPI.getAllCitiesWithFood();

        // 
        const container = document.getElementById('cities-result');
        container.innerHTML = '';

        data.cities.forEach(city => {
            // Create city name and puts it in a span element
            const cityBtn = document.createElement('span');
            cityBtn.textContent = city.name;    // City name
            cityBtn.style.display = 'block';    // Makes the span take full width
            cityBtn.style.flex = '1';

            // Arrow icon
            const arrow = document.createElement('i');
            arrow.className = 'fa-solid fa-chevron-down';   // Fontawesome icon
            arrow.style.marginRight = '8px';                // Space between arrow and city name
            arrow.style.transition = 'transform 0.2s';      // Animation when clicked

            // Container for city name and arrow
            const cityRow = document.createElement('button');
            cityRow.style.display = 'flex';
            cityRow.appendChild(arrow);         // Arrow on the left
            cityRow.appendChild(cityBtn);       // City name on the right

            // Collapsible content div (hidden by default)
            const foodDiv = document.createElement('div');
            foodDiv.style.display = 'none';       // Hidden initially
            foodDiv.style.marginLeft = '20px';    // Indent

            // Toggle for foods - when city name is clicked
            cityBtn.onclick = async () => {

                // When clicked - food visible
                if (foodDiv.style.display === 'none') {
                    // Fetch food data for the city
                    const foodData = await citiesAPI.getCityFood(city.id);

                    foodDiv.innerHTML = foodData.food.length
                        // If foods found, create a div for each food + price
                        ? foodData.food.map(f => `<div>${f.name} - $${f.price}</div>`).join('')

                        // If no foods found, display message
                        : '<div>No foods found</div>';
                    foodDiv.style.display = 'block';
                    arrow.className = 'fa-solid fa-chevron-up';
                } // end if

                // Default - hidden food + arrow down
                else {
                    foodDiv.style.display = 'none';
                    arrow.className = 'fa-solid fa-chevron-down';
                } // end else
                    
            }; // end cityBtn.onclick

            container.appendChild(cityRow);
            container.appendChild(foodDiv);
        });
    } // end try

    // If API is not running, show an alert
    catch (error) {
        console.error('API connection failed:', error);
        alert('Cannot connect to API. Make sure the server is running on http://localhost:3001');
    } // end catch

}; // end window.onload