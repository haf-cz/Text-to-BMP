Introduction
----
Text-to-BMP lets you take your own data and create a BMP image out of it.

Usage: bmpmaker [OPTIONS]
Reads data from stdin

````
Options:
 -w <width>             Choose the width of the image. The height will
                        be automatically determined if -h is not choosed
						
 -h <height>            Choose the height of the image. The width will
                        be automatically determined if -w is not choosed
						
 -o <file>              Place the output in <file>. Standard
                        name is a.bmp
						
 -c <ascii>             If the appliction needs to fill the image with
                        junk data this character will be used. Standard
                        is null
						
 -i                     Prints information about the image on
                        the screen
						
 -h --help              Shows this info
````

Example usage:
````
bmpmaker -h 40 -o my_image.bmp < my_data.txt
````

#### Example rendering
The hitchhikers guide to the galaxy:

![The hitchhikers guide to the galaxy](http://lindell.github.com/Text-to-BMP/hitchhikers.bmp)

![The hitchhikers guide to the galaxy](http://lindell.github.com/Text-to-BMP/hitchhikers.png)