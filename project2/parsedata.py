import pandas as pd

def parse_csv(file_path, size, sparsity, matrix_a_type, matrix_b_type):
    # Read the CSV file
    df = pd.read_csv(file_path)
    
    # Convert 'Size' and 'Sparsity' columns to numeric, handling any invalid values
    df['Size'] = pd.to_numeric(df['Size'], errors='coerce')
    df['Sparsity'] = pd.to_numeric(df['Sparsity'], errors='coerce')
    
    # Filter the dataframe based on the given conditions
    filtered_df = df[
        (df['Size'] == size) & 
        (df['Sparsity'] == sparsity) & 
        (df['Matrix A Type'] == matrix_a_type) & 
        (df['Matrix B Type'] == matrix_b_type)
    ].copy()
    
    # Get the unoptimized time
    unoptimized = df[
        (df['Size'] == size) & 
        (df['Sparsity'] == sparsity) & 
        (df['Matrix A Type'] == matrix_a_type) & 
        (df['Matrix B Type'] == matrix_b_type) & 
        (df['Function'] == 'Unoptimized')
    ]['Time (ms)'].values[0]

    # Calculate the percentage increase for each row in the filtered dataframe
    filtered_df['Time % Decrease'] = ((unoptimized - filtered_df['Time (ms)']) / unoptimized) * 100
    
    # Display the filtered dataframe with the calculated 'Time % Increase'
    filtered_df = filtered_df[['Size', 'Sparsity', 'Matrix A Type', 'Matrix B Type', 'Function', "Threads", "Tile Size", 'Time (ms)', 'Time % Decrease']]
    
    return filtered_df

file_path = 'results.csv'
size = 2500
sparsity = 0.01
matrix_a_type = 'Dense'
matrix_b_type = 'Sparse'

# Parse the CSV and get the filtered dataframe with percentage increase
filtered_df = parse_csv(file_path, size, sparsity, matrix_a_type, matrix_b_type)

# Print the resulting dataframe in markdown table format
print(filtered_df.to_markdown(index=False))
