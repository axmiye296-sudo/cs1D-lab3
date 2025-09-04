#!/usr/bin/env python3
"""
Check what sheets are in the Excel file
"""

import pandas as pd
import sys
import os

def check_excel_sheets(excel_file):
    """Check what sheets are in the Excel file"""
    try:
        # Read Excel file
        excel_file = pd.ExcelFile(excel_file)
        
        print(f"�� Excel file: {excel_file}")
        print(f"📋 Available sheets: {excel_file.sheet_names}")
        
        # Check each sheet
        for sheet_name in excel_file.sheet_names:
            print(f"\n📄 Sheet: '{sheet_name}'")
            df = pd.read_excel(excel_file, sheet_name=sheet_name)
            print(f"   Rows: {len(df)}")
            print(f"   Columns: {list(df.columns)}")
            print(f"   Sample data:")
            print(df.head(3).to_string())
            
    except Exception as e:
        print(f"❌ Error: {e}")

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 check-excel-sheets.py <excel_file>")
        sys.exit(1)
    
    excel_file = sys.argv[1]
    if not os.path.exists(excel_file):
        print(f"❌ File not found: {excel_file}")
        sys.exit(1)
    
    check_excel_sheets(excel_file)

if __name__ == "__main__":
    main()