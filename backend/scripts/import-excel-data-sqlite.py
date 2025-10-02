#!/usr/bin/env python3
"""
Import data from Excel file to SQLite database
"""

import pandas as pd
import sqlite3
import sys
import os

# SQLite database file path
DB_FILE = 'database/cs1d_lab3.db'

def import_from_excel(excel_file):
    """Import all data from Excel file to SQLite"""
    try:
        # Connect to SQLite database
        conn = sqlite3.connect(DB_FILE)
        cursor = conn.cursor()
        
        # Read Excel file
        xls = pd.ExcelFile(excel_file)
        print(f"📋 Available sheets: {xls.sheet_names}")

        # --- Import Cities from 'Distances' and 'New Cities' sheets ---
        print("��️  Importing cities...")
        all_cities = set()
        if 'Distances' in xls.sheet_names:
            df_distances = pd.read_excel(xls, sheet_name='Distances')
            all_cities.update(df_distances['Starting City'].unique())
            all_cities.update(df_distances['Ending City'].unique())
        if 'New Cities' in xls.sheet_names:
            df_new_cities = pd.read_excel(xls, sheet_name='New Cities')
            all_cities.update(df_new_cities['Starting City'].unique())
            all_cities.update(df_new_cities['Ending City'].unique())

        for city_name in sorted(list(all_cities)):
            if pd.notna(city_name):
                cursor.execute("INSERT OR IGNORE INTO cities (name) VALUES (?);", (str(city_name),))
        conn.commit()
        print(f"✅ Imported {len(all_cities)} unique cities.")

        # --- Import Foods from 'Foods' sheet ---
        print("�� Importing foods...")
        if 'Foods' in xls.sheet_names:
            df_foods = pd.read_excel(xls, sheet_name='Foods')
            # Clean up the 'Foods' DataFrame
            # Forward fill 'City' column to associate food items with cities
            df_foods['City'] = df_foods['City'].ffill()
            # Drop rows where 'Traditional Food Item' is NaN (these are the city header rows)
            df_foods = df_foods.dropna(subset=['Traditional Food Item'])
            
            food_count = 0
            for index, row in df_foods.iterrows():
                city_name = row['City']
                food_name = row['Traditional Food Item']
                price = row['Cost']
                
                if pd.notna(city_name) and pd.notna(food_name) and pd.notna(price):
                    # Get city_id
                    cursor.execute("SELECT id FROM cities WHERE name = ?;", (str(city_name),))
                    city_id = cursor.fetchone()
                    if city_id:
                        city_id = city_id[0]
                        cursor.execute(
                            "INSERT OR IGNORE INTO foods (name, city_id, price) VALUES (?, ?, ?);",
                            (str(food_name), city_id, float(price))
                        )
                        food_count += 1
                    else:
                        print(f"⚠️ Warning: City '{city_name}' not found for food '{food_name}'. Skipping.")
            conn.commit()
            print(f"✅ Imported {food_count} food items.")
        else:
            print("❌ Error: Worksheet named 'Foods' not found.")

        # --- Import Distances from 'Distances' and 'New Cities' sheets ---
        print("🛣️  Importing city distances...")
        
        def import_distances_from_df(df, cursor, conn):
            distance_count = 0
            for index, row in df.iterrows():
                from_city_name = row['Starting City']
                to_city_name = row['Ending City']
                distance = row['Kilometers']

                if pd.notna(from_city_name) and pd.notna(to_city_name) and pd.notna(distance):
                    cursor.execute("SELECT id FROM cities WHERE name = ?;", (str(from_city_name),))
                    from_city_id = cursor.fetchone()
                    cursor.execute("SELECT id FROM cities WHERE name = ?;", (str(to_city_name),))
                    to_city_id = cursor.fetchone()

                    if from_city_id and to_city_id:
                        from_city_id = from_city_id[0]
                        to_city_id = to_city_id[0]
                        
                        # Insert distance from A to B
                        cursor.execute(
                            "INSERT INTO city_distances (from_city_id, to_city_id, distance) VALUES (?, ?, ?) ON CONFLICT (from_city_id, to_city_id) DO UPDATE SET distance = excluded.distance;",
                            (from_city_id, to_city_id, float(distance))
                        )
                        distance_count += 1
            conn.commit()
            return distance_count

        total_distances = 0
        if 'Distances' in xls.sheet_names:
            df_distances = pd.read_excel(xls, sheet_name='Distances')
            count = import_distances_from_df(df_distances, cursor, conn)
            total_distances += count
            print(f"✅ Imported {count} distances from 'Distances' sheet.")

        if 'New Cities' in xls.sheet_names:
            df_new_cities = pd.read_excel(xls, sheet_name='New Cities')
            count = import_distances_from_df(df_new_cities, cursor, conn)
            total_distances += count
            print(f"✅ Imported {count} distances from 'New Cities' sheet.")

        print(f"🎉 Data import complete! Total distances: {total_distances}")

    except FileNotFoundError:
        print(f"❌ Error: Excel file '{excel_file}' not found.")
        return False
    except Exception as e:
        print(f"❌ An error occurred during import: {e}")
        return False
    finally:
        if 'conn' in locals() and conn:
            conn.close()
    
    return True

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 import-excel-data-sqlite.py <excel_file_path>")
        sys.exit(1)
    
    excel_file_path = sys.argv[1]
    success = import_from_excel(excel_file_path)
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()
