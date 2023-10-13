# Image-Editor

## Features

- **Negative Filter**
- **Color Replacement**
- **Clarity Enhancement**
- **Gaussian Blur**
- **Grayscale Conversion**
- **Ridge Detection**
- **Noise Reduction**
- **Vignette Effect**
- **Compress and Resize**
- **Dramatic Sepia**

## Installation

1. Clone the repository or download the ZIP file.
2. Сreate the `build` directory.
3. Run the following commands to build the project:
   ```shell
   cmake ..
   make
   ```
## Usage

```shell
# Navigate to the `build` directory
cd build

# Run the Image Editor with the desired image and flags
./main <path_to_image> <flags>
```

### Available Flags:

- **--negative**: Apply a negative filter to the image.

- **--replace_color**: Replace one color with another color in the image.

   Usage: 
   ```shell
   --replace_color <old_color_R> <old_color_G> <old_color_B> <new_color_R> <new_color_G> <new_color_B>


- **--clarity_enhancement**: Enhance the clarity of the image.

- **--gaussian_blur**: Apply Gaussian blur to the image.

- **--gray**: Convert the image to grayscale.

- **--ridge_detection**: Perform ridge detection on the image.

- **--reduce_noise**: Reduce noise in the image.

- **--vignette**: Apply a vignette effect to the image.

- **--cut**: Crop a rectangular region from the image.
  
   Usage:
   ```shell
    --cut <x_position> <y_position> <width> <height>

  
- **--compress**: Compress the image to the specified dimensions.

   Usage:
  ```shell
   --compress <new_width> <new_height>


- **--dramatic_sepia**: Apply a dramatic sepia effect to the image.

- **--help**: Display this documentation.

### Note: The edited image will be saved in the `img` directory.
