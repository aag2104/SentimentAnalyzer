# Assignment 2: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Your Name: Alex Geer

Used free extension: [X] 24 hrs or [ ] 48 hrs

[ ] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## UML Diagram

Add your UML class diagram here.

Replace the following image with your diagram. You can draw it by hand and take a photo.
![UML Class Diagram](UML_Diagram.png)

## Answers

1. How do you train the model and how do you classify a new tweet? Give a short description of the main steps.

    > To train the model, I first opened and parsed the training file, storing sentiments and tweets into Tweet objects. I cleaned and then stored these Tweet objects into a map of id numbers and tweets. I iterated the map through tokenize() and stored each line of words into vector (tweet's sentiment at index 0). I then iterated through the vector and stored the words into a map with their respective ratios good-bad (using Ratio objs). Lastly, I decided whether each word was to be classifed as good or bad by subtracting good occurances minus bad.
    > To classify, I opened and parsed the testing file. I cleaned and stored the tweets into Tweet objs. Then I put the Tweet objs into a map of id numbers and tweets. I then tokenized each tweet and stored the words into a vector. Lastly, I iterated through the vectors and their words, comparing each word to the words in my training map. If a tweet has more good than bad words, it is a good tweet. If a tweet has more bad than good words, it is a bad tweet.

2. How long did your code take for training and what is the time complexity of your training implementation (Big-Oh notation)? Remember that training includes reading the tweets, breaking it into words, counting, ... Explain why you get this complexity (e.g., what does `N` stand for and how do your data structures/algorithms affect the complexity).

   > My code takes 953 ms to train. The time complexity is O(n^3), the portion of my code that opens and parses the training file requires 3 loops inside one another: a for loop and 2 do while loops. Big-Oh relies on the worse case. Because this portion of my code is the most complex (is the highest order term), it is classifed as the Big-Oh of my algrorithm.

3. How long did your code take for classification and what is the time complexity of your classification implementation (Big-Oh notation)? Explain why.

   > My code takes 1407 ms in total, the classification process (just predicting) took 360 ms. The time complexity is O(n^3). Again, just opening and parsing requires 3 loops inside one another. If 2 loops reliant on n equals O(n^2), 3 loops reliant on n equals O(n^3). This is essentially the same implementation as what I used for training. Because this portion of my code is the most complex (is the highest order term), it is classifed as the Big-Oh of my algrorithm.


4. How do you know that you use proper memory management? I.e., how do you know that you do not have a memory leak?

   > I made sure to continuously check my code for memory leaks using Valgrind. Valgrind tells me whether I have memory leaks. When sumbitting this program I, once again, checked to assure I had no memory leaks.

5. What was the most challenging part of the assignment?

   > The most challanging part of this assignment was dealing with pointers. I had a tough time working with the DSStrings. I'm not sure I had a good grasp on how pointers worked inside a program until this assignment. This project forced me to overcome that weakness.