# L.A.W.R.E.N.T.I.A.N.

A system intended to streamline the creation of the "Lawrentian" student newspaper, consisting of a server application and GUI client. Users communicate with the server through the client application, and, depending on their assigned role within the system, can 

* Submit articles for editing
* Browse the editing history of an article
* Submit photographs and illustrations
* Manage off-campus subscriptions and delivery routes
* Track employees' contact information
* Organize the newspaper archives and add issues to it
* Assign writers/photographers to articles

And more. The system's goal is to provide a single interface through which every manager, editor, administrator, and content creator can collaborate over a central database towards the goal of publishing a new issue every week.

## Libraries

* The client GUI application is programmed using the **Qt** framework.

* Server communication is handled with **ZeroC Ice**.

* The server stores most of its data in a **MySQL** database. The exceptions are word documents and images (articles and photos/illustrations) which are handled manually.

By the way, "L.A.W.R.E.N.T.I.A.N." stands for "Lawrence’s Astounding Web-Ready Eellogofusciouhipoppokunurious 
News and Timely Information Assimilation Network". (*Eellogo...* means simply "very good" or "fine".)
