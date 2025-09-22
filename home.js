// UI functions that use the CitiesAPI class
        async function getAllCities() {
            try {
                const data = await citiesAPI.getAllCities();
                document.getElementById('cities-result').innerHTML = '<pre>' + JSON.stringify(data, null, 2) + '</pre>';
            } catch (error) {
                document.getElementById('cities-result').innerHTML = 'Error: ' + error.message;
            }
        }

        async function getAllCitiesWithFood() {
            try {
                const data = await citiesAPI.getAllCitiesWithFood();
                document.getElementById('cities-food-result').innerHTML = '<pre>' + JSON.stringify(data, null, 2) + '</pre>';
            } catch (error) {
                document.getElementById('cities-food-result').innerHTML = 'Error: ' + error.message;
            }
        }

        async function getCityFood() {
            const cityId = document.getElementById('cityId').value;
            try {
                const data = await citiesAPI.getCityFood(cityId);
                document.getElementById('city-food-result').innerHTML = '<pre>' + JSON.stringify(data, null, 2) + '</pre>';
            } catch (error) {
                document.getElementById('city-food-result').innerHTML = 'Error: ' + error.message;
            }
        }

        async function loadCities() {
            try {
                const data = await citiesAPI.getAllCities();
                
                let html = '<h3>Cities (click to see foods):</h3>';
                data.cities.forEach(city => {
                    html += `<div><button onclick="showCityFood(${city.id}, '${city.name}')">${city.name} (ID: ${city.id})</button></div>`;
                });
                document.getElementById('cities-list').innerHTML = html;
            } catch (error) {
                document.getElementById('cities-list').innerHTML = 'Error: ' + error.message;
            }
        }

        async function showCityFood(cityId, cityName) {
            try {
                const data = await citiesAPI.getCityFood(cityId);
                
                let html = `<h4>Foods in ${cityName}:</h4>`;
                if (data.food && data.food.length > 0) {
                    data.food.forEach(food => {
                        html += `<div>${food.name} - $${food.price}</div>`;
                    });
                } else {
                    html += '<div>No foods found</div>';
                }
                document.getElementById('cities-list').innerHTML += html;
            } catch (error) {
                document.getElementById('cities-list').innerHTML += '<div>Error: ' + error.message + '</div>';
            }
        }

        // Check API health on page load
        window.onload = async function() {
            try {
                await citiesAPI.checkHealth();
                console.log('API is running');
            } catch (error) {
                console.error('API connection failed:', error);
                alert('Cannot connect to API. Make sure the server is running on http://localhost:3001');
            }
        };