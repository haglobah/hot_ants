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
                string_list = file.readline().split(",")
                for j in range(y_dim):
                    if string_list[j] == "":
                        data_array[t, i, j] = 0
                    else:
                        data_array[t, i, j] =  float(string_list[j])
        return data_array


def array_to_rgb(array):
    x, y = array.shape
    if np.max(array) == 0: 
        max = 1
    else: 
        max = np.max(array)

    rgb_array = np.zeros((x, y, 3), dtype=np.uint8)

    for i in range(x):
        for j in range(y):
            rgb_array[i, j, :] = [0, 0, array[i, j] / max * 255]
            # if array[i, j] / max > 0.5:
            #     rgb_array[i, j, :] = [(array[i, j] - max / 2) * 2 / max * 255, (array[i, j] - max / 2 ) * 2 / max * 255,255]
            # else:
            #     rgb_array[i, j, :] = [0, 0, array[i, j] / np.max(max * 255, 1)]

    return rgb_array


def make_vid(data_array):
    t, x, y = data_array.shape
    for i in range(t):
        black_white_array = data_array[i]
        cv2.imwrite('out/' + format(i, '05d')+'.jpg', black_white_array)

    frameSize = (1200, 600)

    video_out = cv2.VideoWriter('output_video.m4v', cv2.VideoWriter_fourcc(*'mp4v'), 10, frameSize)

    for file in glob.glob('out/*.jpg'):
        #print(file)
        img = cv2.imread(file)
        resized = cv2.resize(img, frameSize)
        cv2.imwrite(file, resized)
        resized_jpg = cv2.imread(file)
        video_out.write(resized_jpg)

    video_out.release()


# Example usage:
file_path = 'heatHistory.txt'  # Replace 'data.txt' with the path to your text file
data_array = read_data_from_file(file_path)
print(data_array)

#  data_array = np.random.rand(100,100, 100)*256

make_vid(data_array)
