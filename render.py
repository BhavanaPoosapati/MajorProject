import matplotlib.pyplot as plt

# Function to parse lines from user input
def parse_lines(input_str):
    lines = []
    input_str = input_str.strip('{}')
    lines_str = input_str.split('},{')
    for line_str in lines_str:
        line = [float(x) for x in line_str.split(',')]
        lines.append(line)
    return lines

# Get lines for shapes
input_str = input("Enter lines for shape 1 in the form { {x1,y1,x2,y2}, {x3,y3,x4,y4}, ... }: ")
s1 = parse_lines(input_str)

input_str = input("Enter lines for shape 2 in the form { {x1,y1,x2,y2}, {x3,y3,x4,y4}, ... }: ")
s2 = parse_lines(input_str)

# Create a new figure and axis
fig, ax = plt.subplots()

# Plot the shapes
for line in s1:
    x_start, y_start, x_end, y_end = line
    ax.plot([x_start, x_end], [y_start, y_end], 'b-', label='Shape 1')
for line in s2:
    x_start, y_start, x_end, y_end = line
    ax.plot([x_start, x_end], [y_start, y_end], 'r-', label='Shape 2')

# Plot x and y axes
ax.axhline(0, color='k', linewidth=1)
ax.axvline(0, color='k', linewidth=1)

# Set plot limits and labels
ax.set_xlim(-10, 10)
ax.set_ylim(-10, 10)
ax.set_xlabel('X')
ax.set_ylabel('Y')

# Add legend
ax.legend()

# Show the plot
plt.show()
