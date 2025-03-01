import os
import re

# Set the root directory you want to list files from
root_dir = './src'

# Generate YAML configuration for each subdirectory in the root directory
for folder_name in sorted(os.listdir(root_dir)):
    folder_path = os.path.join(root_dir, folder_name)
    if os.path.isdir(folder_path):  # Check if it's a directory
        print(f"- name: {folder_name}")
        print(f"  dir: {folder_name}/")
        print("  files:")
        for file_name in sorted(os.listdir(folder_path)):
            safe_title = re.sub('_', '\\_', file_name[:-4])
            print(f"    - title: {safe_title}")
            print(f"      fname: {file_name}")
