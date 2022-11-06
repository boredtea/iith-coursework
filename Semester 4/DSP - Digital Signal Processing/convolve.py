import numpy as np
import matplotlib.pyplot as plt
import wave
from playsound import playsound

# function for convolving a feature vector with a kernel
def convolve(input, kernel, time_x, time_h):
  input_size = input.size
  kernel_size = kernel.size

  # flipping the kernel
  kernel = np.flip(kernel)
  padding = kernel_size // 2
  output_size = int((input_size - kernel_size + 2 * padding) + 1)

  # padding the input array with zeros on both ends
  padded = np.zeros((input_size + padding * 2))
  # setting inner portion to the input array
  padded[padding:-1 * padding] = input

  output = np.zeros(output_size)
  # filling the output array with the convolved values
  for i in range(output_size):
    output[i] = (kernel * padded[i:i + kernel_size]).sum()