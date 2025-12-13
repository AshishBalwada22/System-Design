1) Association
- has a relationship
i.e user has profile  , user -> profile
2) Inheritance 
- Admin and customer inherit from user. 
triangle arrow
3) interface
- iLogger is a interface and fileLogger implements it
dashed line with triangle
4) Aggregation
- customer 'has' order but order can live on their own.
customer   (hollow diamond)(line)  order    (order)0..*(customer)
5) Composition
- order is tightly bound with address, if order dies then address goes with it.
- order  (filled diamond)(line)   address   (1..*)

Association - 
basic link between two classes.
"uses a" / "work with a"/  "talk to a"
i.e A customer uses/places a order

Aggregation - 
whole-part relationship where one class contains other but they can live on their own.
"has a" / "is made up of"
i.e A team has employees

Composition - 
whole-part relationship but part cannot live without whole.
"owns a" / "is composed of" / "cannot live without"
i.e A book is composed of chapters.

Inheritance - 
one class share feature with another.
"is a" / "is kind of"
i.e a manager is a kind of employee

Service
calculator
renderer
notifier
validator
parser

