# Tests
The project includes simple unit tests implemented in the `libds-tests` folder. The tests are included in the build system, so they are automatically compiled when using the `ninja` command in the `build` folder. Selective compilation of tests is possible with the command:
```bash
ninja ds-tests
```
The tests are run with the command:
```bash
./libds.tests/ds-tests
```
A clearer output of the tests can be displayed using the `summary` argument:
```bash
./libds.tests/ds-tests summary
```





# Documentation

## UML
The project contains documentation for individual exercises in the form of UML diagrams. The [PlantUML](https://plantuml.com/) tool is used to create the diagrams. This tool creates UML diagrams based on text descriptions. These descriptions are located in the folder:
```
doc/uml/
```
To generate diagrams, we can use the [PlantUML](https://marketplace.visualstudio.com/items?itemName=jebbs.plantuml) extension. We install it with the command:
```bash
code --install-extension jebbs.plantuml --force
```
We generate a UML diagram by opening the source file (`*.puml`) and pressing the keyboard shortcut `Alt+D`. UML diagrams can be rendered **locally** or on a **server**.

### Rendering on the server
The server address must be added to the user settings. The freely available official server can be used here. Open the user settings with the shortcut `Ctrl+Shift+P`, type and select the option **Open User Settings (JSON)**. Add the following settings to the open JSON file:
```JSON
{
    "plantuml.render": "PlantUMLServer",
    "plantuml.server": "https://www.plantuml.com/plantuml",
}
```

### Local rendering
For local rendering, Java must be installed and visible (in the `PATH` variable) in the environment from which we run Visual Studio Code.

First, we need to check if it is already installed in Windows. Open **PowerShell** and enter the command:
```PowerShell
Get-Command java
```
If it is installed, its location will be displayed; otherwise, an error will be displayed and Java will need to be installed, for example with the command:
```PowerShell
winget install --id BellSoft.LibericaJDK.25 --exact --source winget
```

If we want Java to be visible when running Visual Studio Code from the Bash interpreter with the command:
```bash
code .
```
we need to edit the `PATH` variable in the `~/.bashrc` file:
```bash
echo "export PATH=\"/c/Program Files/BellSoft/LibericaJDK-25/bin:\$PATH\"" >> ~/.bashrc
```
The path `/c/Program Files/BellSoft/LibericaJDK-25/bin` must, of course, be modified according to the location of Java obtained in the manner described above. Do not forget to use forward slashes `/`.



## Doxygen
All classes and functions contain documentation comments. Based on the documentation comments, it is possible to generate external documentation in HTML format using the [Doxygen](https://www.doxygen.nl/index.html) tool. In the UCRT64 environment, we install it with the command:
```bash
pacman -S mingw-w64-ucrt-x86_64-doxygen
```
Generate the documentation with the command run in the project root:
```bash
doxygen doc/Doxyfile
```
The generated documentation is saved in the folder:
```
doc/html/
```
Open the documentation by opening the file:
```
doc/html/index.html
```
in a web browser.


## Semestral Project
Prepare the documentation for your semestral project using the template found in the file `doc/semestral_project/documentation-en.markdown`. The template uses the [Pandoc markdown](https://garrettgman.github.io/rmarkdown/authoring_pandoc_markdown.html) format. Visual Studio Code will show you the basic form of the final document.

### Generating a PDF version of the documentation
**You do not need to create a PDF version; the teachers will do it for you. If you want, you can replicate our procedure.**

 We will use the [Pandoc](https://pandoc.org/) tool to create the PDF file. Unfortunately, this tool is not found in the MSYS project repositories, so it needs to be installed on Windows using the following command run in the PowerShell interpreter:
```PowerShell
winget install --id JohnMacFarlane.Pandoc --exact --source winget
```
Pandoc uses [LaTeX](https://www.latex-project.org/) to create PDF files. This is already available in the MSYS project repositories, so we will install it using the following command run in the Bash interpreter (UCRT64):
```Bash
pacman -S \
  mingw-w64-ucrt-x86_64-texlive-bibtex-extra \
  mingw-w64-ucrt-x86_64-texlive-bin \
  mingw-w64-ucrt-x86_64-texlive-core \
  mingw-w64-ucrt-x86_64-texlive-extra-utils \
  mingw-w64-ucrt-x86_64-texlive-font-utils \
  mingw-w64-ucrt-x86_64-texlive-fonts-extra \
  mingw-w64-ucrt-x86_64-texlive-fonts-recommended \
  mingw-w64-ucrt-x86_64-texlive-formats-extra \
  mingw-w64-ucrt-x86_64-texlive-humanities \
  mingw-w64-ucrt-x86_64-texlive-lang-czechslovak \
  mingw-w64-ucrt-x86_64-texlive-lang-english \
  mingw-w64-ucrt-x86_64-texlive-lang-european \
  mingw-w64-ucrt-x86_64-texlive-latex-extra \
  mingw-w64-ucrt-x86_64-texlive-latex-recommended \
  mingw-w64-ucrt-x86_64-texlive-luatex \
  mingw-w64-ucrt-x86_64-texlive-metapost \
  mingw-w64-ucrt-x86_64-texlive-pictures \
  mingw-w64-ucrt-x86_64-texlive-plain-generic \
  mingw-w64-ucrt-x86_64-texlive-pstricks \
  mingw-w64-ucrt-x86_64-texlive-publishers \
  mingw-w64-ucrt-x86_64-texlive-science
```
Finally, in order to use `pandoc` from the Bash interpreter, the following line must be added:
```Bash
export PATH="/c/Users/mrena/AppData/Local/Pandoc:$PATH"
```
to the end of the `~/.bashrc` file (`/c/msys64/home/{UPN}/.bashrc`). We can do this, for example, with the command:
```Bash
echo "export PATH=\"/c/Users/mrena/AppData/Local/Pandoc:\$PATH\""
```
We will create a PDF document with the documentation by running the following command:
```Bash
pandoc documentation.markdown --from markdown+lists_without_preceding_blankline --to pdf --template=template.tex --output documentation.pdf
```
in the documentation folder (`cd doc/semestral_project`).
