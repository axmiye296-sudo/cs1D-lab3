async function fetchCities() {
    try {
        const response = await fetch('');
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }

        const data = await response.json();
        console.log(data);
        return data;
    } catch (error) {
        console.error('Error fetching cities: ', error);
        throw error;
    }
}