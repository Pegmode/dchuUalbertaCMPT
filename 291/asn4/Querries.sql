CREATE TABLE Parts (

partNumber INTEGER, -- a UPC code 

partPrice INTEGER, -- in the [1, 100] range

needsPart INTEGER, -- a UPC code

madeIn TEXT, -- a country (2 letters) code 

PRIMARY KEY(partNumber)

);