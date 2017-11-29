# Advanced Filestreams
It's a small - currently in development - libray for a more comfortable access to filestreams and mainly a helper for XML file handling.

# How to use? #
For the purpose of testing you may compile the project and run it. It will search for a "test.xml" and tries to parse and read it.

# Known Bugs #
At the moment, the following bugs are known
 -  If there are Spaces in the content or in attributes, the programm may think it's a tag or an attribute. Fixing this behaviour is on my High-Priority-List. 
- Reading of Data, which starts not with Spaces, but with Tabs.
