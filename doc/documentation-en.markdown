---
author: Name Surname
lang: English
---

\pagebreak

*This template uses the [Pandoc markdown](https://garrettgman.github.io/rmarkdown/authoring_pandoc_markdown.html) format. The link above provides documentation on formatting various parts of the document. The template contains examples of basic formatting, which is sufficient for preparing documentation. **Do not change the structure of the document (sections, subsections, and page breaks (`\pagebreak`)).** Remove text formatted in italics after using the template. Edit the author's name in the document header.


# Application design
*In this section, describe the design of your application. Supplement the design with a UML class diagram -- an internal view of your own classes; the used UML is sufficient in the form of a class header.*

*Place images in the `img` subfolder. Use the following syntax for insertion:*

![UML class diagram](img/doc-uml-example.png "Alternative image description"){ width=35% }

## UML
*We **recommend** using the [PlantUML](https://plantuml.com/) tool to create UML diagrams. However, you can also create UML in any other tool you prefer.*

\pagebreak

# Data structures used
*In this section, list the data structures you have used. Justify the appropriateness of each structure. At the end of the section, list the structures that are taken from the labs.*

## Taken data structures
The implementation of the following data structures is taken from the labs:
- Structure 1
- Structure 2

## Structure 1
*Justify the appropriateness of using the structure.*

## Structure 2
*Justify the appropriateness of using the structure.*

\pagebreak

# Additional requirements
*If you have not completed any of the levels, delete the relevant subsection.*

## Level 1
*Additional requirements for the level in terms of the assignment.*

## Level 2
*Additional requirements for the level in terms of the assignment.*

## Level 3
*Additional requirements for the level as specified in the assignment.*

## Level 4
*Additional requirements for the level as specified in the assignment.*

\pagebreak

# User manual
*In this section, describe how your application is used.*

\pagebreak

# Programmer's Manual
*In this section, describe how a programmer would proceed if they wanted to extend your application. Use UML diagrams and/or source code examples for the description.*

```cpp
#include <iostream>
int main() {
  std::cout << "Hello world!\n";
}
```
