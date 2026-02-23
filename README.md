I HATE MY SELF AND LOVE C++- this what i will put as a tile if it was book

The program relies on very little amount of premaid function or libraries 
so far i used only fstream,iostream,string this is not beacuse i belive i will write better function
quite the opposite my shit gonna be less optimized for sure but i like it

The goal of the program is simple 
We have the abiliy to draw and add label the program should be able to recognize any varations of our drawing that is connected to specif label
i have ZERO knowledge how ai and machine learning works so the way i though may not work

i divide the "board" into 9 segments each segment gonna have its own value based what it has inside for example * = 2 points and " " 1 point 
after the program calculates the value of each segment its gonna create a "tree" which each parent can have up to 18 kids that crazy ngl
kids have priority from the leftest which is lowest to righest which is highest the program gonna try to "predict" the next segment based on the priority
when it choose the highest child priority and its wrong then it lose its spot and goes left then it tryies untill it gets to the closest and if not it chooses the closest value
by doing value of already listed segments - what is drawn and like this for each segment untill it comes to the end where only one child should reside and that is the "guess"
then it comapres it with the answer if its correct whataver changes were made it stays there if not it goes backwards from the answer to the top makinga nessecarry changes
