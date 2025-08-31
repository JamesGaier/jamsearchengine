# Jam Search!
## Features
 * Indexes webpages based on a series of "seed" URLS using a basic Breadth First Search
 * Given a keyword searches indexed websites for matching URLS
 * Sends requester back a list of pairs of URLS and descriptions based on keyword query
 * Web Crawler respects politeness rules
    * Ignores websites with robots.txt rules (For simplicity and for now)
    * follows a 15 second interval for webpage access
    * Avoids "spider traps" or any website that contains a query in them
## Process
1. Use the project as a template in GitHub
2. Build the project using `./build.sh`