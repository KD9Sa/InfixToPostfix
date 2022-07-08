# Infix To Postfix
Receives an infix string (e.g. 2 + 3 * ( 7 - 5 ) / 2 ). Next, transfers it into its postfix form. Finally, evaluates the equation in its postfix form.

You may notice two push functions, 2 pop functions, 2 init functions...etc. The first is called with the original name (e.g. push) and the second has a preceding f (e.g. fpush). The f refers to "float". The reason for using 2 different functions for each action is to deal with division. After performing the division, it wasn't possible to convert the floating-point number back into a char type, so a floating point functions were used for that reason.
