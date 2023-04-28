# temp sensors sql #

A framework on linux to collect the data from temperature sensors and store the readinds in a 
local database.

Written primarily as a Raspberry pi project this library is an exercise in a
basic driver, sql and threading implementation.

As of writing this README the project is incomplete
Features currently in a partially completed state:
        Validation of file directories, if the directory doesn't exist or doesn't allow access
        a warning is printed to stderr.

        The skeleton of a logging thread. A threat that runs seperate from the primary threat that 
        could potentially validate the parameters of the program occasionally on some defined
        time basis.

A majour work in progress feature is a driver system for reading sensors.
        Since it cannot be assumed that each temperature sensor has the same method of reading, 
        unique code has to be written to handle the reading.
        The codebase goal is to implement a method to have a handle on N sensors of M different 
        types, but the interface to access the functions of these sensors are generic.

        An sql module that will create a database if needed and write data to this database.

The ultimate intention is for this utility to run as a background program that will
occasionally wake up, collect all the readings of specified (or wildcard *) compatible sensors
and store their measurement, time of reading and potential unique ID into an SQLite3 database. 

Application with current scope is somewhat limited due to the project only focussing on accessing
local sensors. 

The personal application (for me, the author) is to have a simple set-and-forget long term simple
temerature measuring utility to measure a variety of zones within ~2m of a raspberry pi.
i.e. the temperature of a roof space compared to the room. Temperatures of outside vs inside
throughout the day.