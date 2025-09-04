-- Database Schema
-- Complete schema for all tables

-- Create cities table
CREATE TABLE IF NOT EXISTS cities (
    id SERIAL PRIMARY KEY,
    name TEXT UNIQUE NOT NULL
);

-- Create foods table
CREATE TABLE IF NOT EXISTS foods (
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL,
    city_id INTEGER REFERENCES cities(id) ON DELETE CASCADE,
    price NUMERIC(10,2) NOT NULL CHECK (price >= 0)
);

-- Create city_distances table
CREATE TABLE IF NOT EXISTS city_distances (
    from_city_id INTEGER REFERENCES cities(id) ON DELETE CASCADE,
    to_city_id INTEGER REFERENCES cities(id) ON DELETE CASCADE,
    distance NUMERIC(10,2) NOT NULL CHECK (distance >= 0),
    PRIMARY KEY (from_city_id, to_city_id)
);

-- Create trips table
CREATE TABLE IF NOT EXISTS trips (
    id SERIAL PRIMARY KEY,
    start_city_id INTEGER REFERENCES cities(id) ON DELETE SET NULL,
    trip_type TEXT NOT NULL,
    total_distance NUMERIC(10,2) CHECK (total_distance >= 0)
);

-- Create trip_cities table
CREATE TABLE IF NOT EXISTS trip_cities (
    id SERIAL PRIMARY KEY,
    trip_id INTEGER REFERENCES trips(id) ON DELETE CASCADE,
    city_id INTEGER REFERENCES cities(id) ON DELETE CASCADE,
    visit_order INTEGER NOT NULL CHECK (visit_order > 0),
    UNIQUE(trip_id, visit_order)
);

-- Create purchases table
CREATE TABLE IF NOT EXISTS purchases (
    id SERIAL PRIMARY KEY,
    city_id INTEGER REFERENCES cities(id) ON DELETE CASCADE,
    food_id INTEGER REFERENCES foods(id) ON DELETE CASCADE,
    quantity INTEGER NOT NULL CHECK (quantity > 0),
    trip_id INTEGER REFERENCES trips(id) ON DELETE SET NULL
);

-- Create users table
CREATE TABLE IF NOT EXISTS users (
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL,
    role TEXT NOT NULL
);

-- Create indexes for better performance
-- Cities indexes
CREATE INDEX IF NOT EXISTS idx_cities_name ON cities(name);

-- Foods indexes
CREATE INDEX IF NOT EXISTS idx_foods_city_id ON foods(city_id);
CREATE INDEX IF NOT EXISTS idx_foods_name ON foods(name);
CREATE INDEX IF NOT EXISTS idx_foods_price ON foods(price);

-- City distances indexes
CREATE INDEX IF NOT EXISTS idx_city_distances_from ON city_distances(from_city_id);
CREATE INDEX IF NOT EXISTS idx_city_distances_to ON city_distances(to_city_id);
CREATE INDEX IF NOT EXISTS idx_city_distances_distance ON city_distances(distance);

-- Trips indexes
CREATE INDEX IF NOT EXISTS idx_trips_start_city ON trips(start_city_id);
CREATE INDEX IF NOT EXISTS idx_trips_type ON trips(trip_type);
CREATE INDEX IF NOT EXISTS idx_trips_total_distance ON trips(total_distance);

-- Trip cities indexes
CREATE INDEX IF NOT EXISTS idx_trip_cities_trip_id ON trip_cities(trip_id);
CREATE INDEX IF NOT EXISTS idx_trip_cities_city_id ON trip_cities(city_id);
CREATE INDEX IF NOT EXISTS idx_trip_cities_visit_order ON trip_cities(visit_order);

-- Purchases indexes
CREATE INDEX IF NOT EXISTS idx_purchases_city_id ON purchases(city_id);
CREATE INDEX IF NOT EXISTS idx_purchases_food_id ON purchases(food_id);
CREATE INDEX IF NOT EXISTS idx_purchases_trip_id ON purchases(trip_id);
CREATE INDEX IF NOT EXISTS idx_purchases_quantity ON purchases(quantity);

-- Users indexes
CREATE INDEX IF NOT EXISTS idx_users_name ON users(name);
CREATE INDEX IF NOT EXISTS idx_users_role ON users(role);