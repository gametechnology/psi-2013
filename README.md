#Project Stella Incognita#
## Source Tree ##
Assets
> In this map all of the images/models and other content will be placed.

Bin
> This folder will hold all the executables of the projects.

Build
> This folder holds all the solution and project files. Every solution has his own folder and every Project in the Solution has his own sub-folder. 
> So for example: the solution Example has the folder 'Example' in the 'build' folder. The Example folder holds a 'ExampleProject' folder with the project files.
>
> !!! IMPORTANT NOTE !!!
>
> You should ALWAYS add the .sdf file to the .gitignore. The .sdf files can grow huge in size and will be rebuild every time you build the project. So the files MUST be excluded from a commit to avoid cluttering the repo with huge, useless files.

Docs
> This folder holds the documentation of the code and the libraries. 

Include
> This folder holds all the include files. It is advised to use sub-folder if there are include files from multiple libraries. We want to avoid merging all those files in one folder.

Lib
> This folder holds all the library (.lib) files.

Source
> This folder has multiple sub-folders for every project. Those sub-folders hold the source code of the corresponding projects. These folders will also hold the header (.h) files.
> The folder also holds the source files of the libraries. The code is just for reference. It is a better idea to use the documentation included in the 'docs' folder for documentation. There is some pretty elaborate documentation generated with doxygen.

Temp
> This folder holds all the debug data. All the data in the DEBUG folders MUST be added to the .gitignore to avoid cluttering the repo with useless data.

Tools
> This folder holds all the tools used in the code.
