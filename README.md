# cs1D-lab3

TO DO

- [x] 1. ~~Put repeating classes in global.css file~~

- [ ] 2. Fix log in page :
    [ ] a. Remove "name" and change it to make user input a code to login to admin

    [ ] b. Add a button to allow traveler to go to home page 


- [ ] 3. Figure out how to make createTrip have certain starting locations based off of option chosen from starting location

- - - 

To run the code do the following:

1. In terminal type
node sever.js

* This will allow the data to appear if you do not do this you will get an error saying API cannot connect. Terminal will not work while server is running

2. Terminal should say the following if it is sucessful: 
"API server running on http://localhost:3001"

3. Right click HTML file you want to preview and click:
"Open with Live Server"

4. To stop running / use terminal again type the following in the terminal:
"Ctrl" + "c"

- - -

Varaibles (in global.css)
Used for consistency. It allows us to make changes faster too, we won't need to search through all css files to manually change anything.

When declaring variables please keep them in the global.css file. Feel free to change the variable names to something better. Better examples are in any css file

How to use:
    1. Go to any css file of your choice. It will work with any css file include global.css file
    
    2. When filling out a style where you can use a varaible do:
        var(--varName)
    
        *change varName to varaible name don't change anything else

Example:
--background: #ffffff;  (varaible declared in global.css)

#container {
    background: var(--background); (in any CSS file sets background to color declared in global.css)
}

- - -

DIRECTORY / FILES

adminEdit

homepage when admin logs in, allows admin to edit cities and foods

    - no files yet

- - -

createTrip

traveler UI allowing traveler to add cities to their trip

    - creatTrip.css
    - createTrip.html
    - createTrip.js

- - -

home

traveler UI showing all the cities

    - home.css
    - home.html
    - home.js

- - -

login

login page for admin

    - login.css
    - login.html

- - - 

summaryTrip

all traveler selected cities

    - no files yet

- - -

global.css

universal global styles used on all pages

- - -

server.js + cities.js

for APIs idk too much yet it makes the APIs work

- - -

mockData.js

fake data used for testing
