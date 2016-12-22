Name: Sandeep Suresh 
Email: Sureshsa@usc.edu 
Id#: 7720774451

Prelab Questions:
1. We need to ensure that the center of the kernel can be at the edges,
   so max we need to add 6 more rows and columns for an 11 by 11 kernel.
   Thus, we would have the largest image at 266x266. 
   The upper-left pixel of the original image would be at (N/2, N/2).
   The lower-right pixel of the original image would be at whatever
   the original size of the image was. So if it was originally a 256x256 
   image then the index of the lower-right pixel would be (256,256)
   
2. If we used the raw values then the brightness of the image would
   have changed. The values for Sigma 2 and N = 3 is: 
   
   
Experimentation: 
1. As you vary sigma and hold N constant, there doesn't seem to be a
   noticable differencebetween the results. However, when you vary the 
   kernel size and keep sigma constant, there seems to be a noticable
   change. As the kernel size increases, the pictures becomes more blury.


2. The sobel filter seems to be emphasizing edges in any picture.


3. The unsharp filter in theory adds a fraction of a detailed map to the 
   original image. A detailed map is the original image subtracted by the 
   blurred image. So trying to unsharp a blurred image wouldn't revert it 
   to the original image because you would still be blurring the already
   blurred image and attempting to create a detailed map of it, then adding 
   a fraction of it to the originally blurred image. 


4. In the inner most loop of the convolution function there are N squared
   number of terms being summed up, so the number of calculations grows
   quadratically as N increases. 
