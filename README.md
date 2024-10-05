I decided to make a really simple code that portrays the ray tracer challenge, which requires some knowledge in vectors, especially matrices. Because the only language I am really proficient in is CSS, I decided to use CSS as my language for this project. At the start, I was quite hesitant about this project because it was my first time including graphics and a canvas for my final product of a code. However, I really wanted to challenge myself on using my coding skills to try something new and the ray tracing challenge was a great fit. 

For the first few weeks, I mostly had struggles on how to build the canvas. Once I had solved this problem, everything seemed to make a lot more sense. Using the book “The Ray Tracer Challenge” by Jamis Buck, I learned about the core concepts that are needed for this challenge such as matrices, lighting, shadows, and colors. The more I read and researched about the ray tracer challenge, I was able to learn and see how the vectors worked together to make up a sphere that looks quite realistic.

I included really basic codes, such as arithmetic functions, unit vector functions, and normalization functions of Tuples and colors at first. As shown in the book I have mentioned, I started off with easy coding, such as making a projectile. Then I used the assert code to make the overall structure not too complicated.

Now, that’s it for the basic codes and let’s go over the sphere. Different factors were used to build the sphere, such as the light ambience, light diffusion, light shininess, or the specular highlight. The code for these can be checked out on my GitHub account: 

Only going over the important code, this was how the fundamental code’s sphere looked like. This code plays a role as the main code that really determines how realistic my sphere would look, including the direction of the light, size, and the color of my sphere. 

<img width="890" alt="Screenshot 2024-10-05 at 11 39 14 PM-min" src="https://github.com/user-attachments/assets/acaab151-a259-4462-81a2-619da6b38a7b">

I was able to adjust the code to make different types of spheres as shown below. (If I didn’t include, the size code, it means that the radius is 1.0)

<img width="923" alt="Screenshot 2024-10-05 at 11 40 42 PM-min" src="https://github.com/user-attachments/assets/80d0fcf3-7c9e-4197-b0db-5091843fdf76">
<img width="958" alt="Screenshot 2024-10-05 at 11 40 37 PM-min" src="https://github.com/user-attachments/assets/6c080080-8849-4f90-895c-f326239f836b">
<img width="962" alt="Screenshot 2024-10-05 at 11 40 30 PM-min" src="https://github.com/user-attachments/assets/3e8fc2ca-abe8-4970-b9d8-e2fe1e70ea0b">
<img width="958" alt="Screenshot 2024-10-05 at 11 40 12 PM-min" src="https://github.com/user-attachments/assets/4c08385c-3cd6-4d1b-9302-c8b1c5feaf25">


After adjusting the spheres, I got the rgb codes of each of the pixels on the main. 
<img width="906" alt="Screenshot 2024-10-05 at 11 40 47 PM-min" src="https://github.com/user-attachments/assets/dae936a9-6acf-454b-b160-a9fe12142718">
How this works is it gets the ratio of r, g, and b and then multiplies 255 to find the whole ratio out of 255. 

Then I put the output on a separate file named “ray_final.ppm”. 
<img width="978" alt="Screenshot 2024-10-05 at 11 41 02 PM-min" src="https://github.com/user-attachments/assets/657b4925-7e84-4944-88ae-b8ed7d00ba4a">
<img width="1027" alt="Screenshot 2024-10-05 at 11 40 54 PM-min" src="https://github.com/user-attachments/assets/77085cca-67fd-4d19-a0e1-b0c9f29d526d">

This is what the “ray_final.ppm” file looked like.
After all these 379 lines of coding, I got a code that can perfectly display a sphere that I can customize on my own. In the end, building a ray tracer was a great start to learn coding, especially in a graphic way. Finally, this project showed me that even when I’m outside my comfort zone, I can learn, adapt, and create something I’m proud of.
