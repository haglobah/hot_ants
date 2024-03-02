import numpy as np
import cv2
import glob


def read_data_from_file(file_path):
    with open(file_path, 'r') as file:
        # Read the first line to get dimensions
        time_steps, x_dim, y_dim = map(int, file.readline().strip().split(', '))

        # Initialize a NumPy array to store the data
        data_array = np.zeros((time_steps, x_dim, y_dim))

        # Read the remaining lines and fill in the array
        for t in range(time_steps):
            for i in range(x_dim):
                row_values = list(map(float, file.readline().strip().split(',')))
                data_array[t, i, :] = row_values

        return data_array


def array_to_rgb(array):
    x, y = array.shape
    max = np.max(array)

    rgb_array = np.zeros((x, y, 3), dtype=np.uint8)

    for i in range(x):
        for j in range(y):
            if array[i,j]/max > 0.5:
                rgb_array[i,j,:]=[(array[i,j]-max/2)*2/max*255,(array[i,j]-max/2)*2/max*255,255]
            else:
                rgb_array[i,j,:]=[0,0,array[i,j]/max*255]

    return rgb_array


def make_vid(data_array):
    t, x, y = data_array.shape
    for i in range(t):
        rgb_array = array_to_rgb(data_array[i])
        cv2.imwrite('out/' +format(i, '05d')+'.jpg', rgb_array)

    frameSize = (x, y)

    out = cv2.VideoWriter('out/output_video.m4v', cv2.VideoWriter_fourcc(*'mp4v'), 10, frameSize)

    for file in glob.glob('out/*.jpg'):
        #print(file)
        img = cv2.imread(file)
        out.write(img)

    out.release()


# Example usage:
file_path = 'res/test_data.txt'  # Replace 'data.txt' with the path to your text file
data_array = read_data_from_file(file_path)
print(data_array)

data_array = np.random.rand(100,100, 100)*256

make_vid(data_array)
