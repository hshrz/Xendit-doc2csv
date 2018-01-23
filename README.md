# Xendit-doc2csv
Converts card statements into CSV

# How to use
In order to convert the DocX file to a CSV, the DocX file must first be converted to a text file. One way to do this is to open the file and then "Save as" a plain text file using Microsoft Word. After the document has been converted to a  text file you can run this converter to generate a formatted CSV file.

The program runs with two arguments:
- the path to the superset CSV file (to extract the merchant number)
- the path to the converted doc file

*Example*
 
Running this would convert the 20/11/2017 document to a CSV using the merchant numbers from the Superset CSV provided:

```
doc2csv sqllab_cc_authorizations_20180117T122752.csv 20112017.txt
```
