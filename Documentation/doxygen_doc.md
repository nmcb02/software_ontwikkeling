# Doxygen

- [Description](#description)
- [Installation](#installation)
- [Setting up doxywizard](#setting-up-doxywizard)
- [Running doxywizard](#running-doxywizard)
- [Opening documentation with HTML file](#opening-documentation-with-html-file)
- [Regenerating and opening documentation with Doxyfile](#regenerating-and-opening-documentation-with-doxyfile)

## Description

In this document the installation and usage for doxygen is explained.

## Installation

For the installation of doxygen follow the steps on the following website, for the platform your using: https://www.doxygen.nl/download.html

During the installation you can click on next after each step, nothing should really be changed. Unless you want a different installation folder of course, you can change the installation path then.

## Setting up doxywizard

After installing, you should now be able to open the doxywizard application.

1. First the working directory should be selected (should be your repositort directory)
2. After this under the tab wizard, write project name, synopsis, etc.
3. Now the source code folder should be selected in the same tab as before (folder where your main is located)
4. Lastly the folder for generating doxygen documentation (this can be a folder called "Doxygen" in your repository)

## Running doxywizard

After setting up the wizard the documentation can be generated.

1. Go to the tab run
2. Click on run doxygen
3. After completion, click on show HTML output
4. Lastly don't forget to safe the Doxyfile to make it simpler to update your documentation (You can save this out of the Doxygen folder, so just in your home folder from your repository)

Now your documentation should be visible.

## Opening documentation with HTML file

Opening the documentation when not in the wizard is very simple.

1. Open the folder where the Doxygen documentation is generated
2. Open the HTML folder if available, otherwhise move to next step
3. Open the index.html file

The documentation should now open

## Regenerating and opening documentation with Doxyfile

Another option is to regenerate and open documentation with the "Doxyfile". If the Doxywizard setup was saved, then there should be a Doxyfile in your repository.

1. Open Doxywizard
2. On the top left click on file, and then "open..."
3. Choose the desired Doxyfile you want to open.
4. Open it
5. All your old settings should now be visible.
6. If needed change some paths, otherwhise go to the run tab and repeat the steps in [Running doxywizard](#running-doxywizard)
