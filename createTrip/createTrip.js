// UI functions that use the CitiesAPI class

// Arrays to keep track of cities
let availableCities = [];   // City List - Cities available to add
let selectedCities = [];    // My List - Cities that have been selected

// Check API health on page load
window.onload = async function() {
    try {
        await citiesAPI.checkHealth();
        console.log('API is running');

        // Fetch all cities
        const data = await citiesAPI.getAllCities();
        availableCities = [...data.cities]; // Copy all cities to available list
        
        // Displays City Lists / list of cities to choose from
        renderAvailableCities();

        // Displays My List / list of selected cities
        renderSelectedCities();
        
    } // end try

    catch (error) {
        console.error('API connection failed:', error);
        alert('Cannot connect to API. Make sure the server is running on http://localhost:3001');
    } // end catch
}; // end window.onload

// Render the left side list (available cities)
function renderAvailableCities() {
    const container = document.getElementById('cities-result');
    container.innerHTML = '';

    availableCities.forEach(city => {
        // Container for city row - will hold city name and plus button
        const cityRow = document.createElement('div');
        cityRow.className = 'city-row';

        // City name
        const cityName = document.createElement('span');
        cityName.textContent = city.name;

        // Plus button
        const plusBtn = document.createElement('button');
        plusBtn.innerHTML = '<i class="fa-solid fa-plus"></i>';

        // Add city to selected list when plus is clicked
        plusBtn.onclick = () => addCityToSelected(city);

        // Will display city name and plus button
        cityRow.appendChild(cityName);
        cityRow.appendChild(plusBtn);
        container.appendChild(cityRow);
    });
}

// Render the right side list (selected cities)
function renderSelectedCities() {
    const container = document.getElementById('selected-cities-result');
    container.innerHTML = ''; // Clear existing content

    // Function for when city is selected
    selectedCities.forEach((city, index) => {
        // Container for city row
        const cityRow = document.createElement('div');
        cityRow.className = 'selected-city-row';
        cityRow.draggable = true;                   // Make the row draggable
        cityRow.dataset.cityId = city.id;

        // Number indicator - will change when reordered
        const numberSpan = document.createElement('span');
        numberSpan.className = 'number';
        numberSpan.textContent = (index + 1) + '.';

        // City name
        const cityName = document.createElement('span');
        cityName.className = 'city-name';
        cityName.textContent = city.name;

        // Minus button
        const minusBtn = document.createElement('button');
        minusBtn.className = 'minus-btn';
        minusBtn.innerHTML = '<i class="fa-solid fa-minus"></i>';

        // Remove city from selected list when minus is clicked
        minusBtn.onclick = () => removeCityFromSelected(city);

        // When drag starts
        cityRow.ondragstart = (e) => {
            e.dataTransfer.setData('text/plain', index);
            cityRow.classList.add('dragging');
        };

        cityRow.ondragend = () => {
            cityRow.classList.remove('dragging');
        };

        cityRow.ondragover = (e) => {
            e.preventDefault();
        };

        // When city dropped
        cityRow.ondrop = (e) => {
            e.preventDefault();
            const draggedIndex = parseInt(e.dataTransfer.getData('text/plain'));
            const targetIndex = index;
            
            if (draggedIndex !== targetIndex) {
                // Reorder the array
                const draggedCity = selectedCities.splice(draggedIndex, 1)[0];
                selectedCities.splice(targetIndex, 0, draggedCity);
                renderSelectedCities();
            }
        };

        cityRow.appendChild(numberSpan);
        cityRow.appendChild(cityName);
        cityRow.appendChild(minusBtn);
        container.appendChild(cityRow);
        
    }); // end selectedCities.forEach
}

// Add city to selected list
function addCityToSelected(city) {
    // Remove from available cities
    availableCities = availableCities.filter(c => c.id !== city.id);
    // Add to selected cities
    selectedCities.push(city);
    
    // Re-render both lists
    renderAvailableCities();
    renderSelectedCities();
}

// Remove city from selected list
function removeCityFromSelected(city) {
    // Remove from selected cities
    selectedCities = selectedCities.filter(c => c.id !== city.id);
    // Add back to available cities
    availableCities.push(city);
    
    // Re-render both lists
    renderAvailableCities();
    renderSelectedCities();
}

// Save the selected cities list and navigate to next page
function saveListAndSubmit() {
    // Check if user has selected any cities
    if (selectedCities.length === 0) {
        alert('Please select at least one city before submitting!');
        return;
    }
    
    // Save the selected cities to localStorage (or you could send to server)
    localStorage.setItem('selectedCities', JSON.stringify(selectedCities));
    
    // Optional: Show confirmation
    console.log('Saved cities:', selectedCities);
    
    // Navigate to the next page - replace 'nextPage.html' with your target page
    window.location.href = '../summaryTrip/summaryTrip.html';
}