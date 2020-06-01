import pyzpk

min_element = 0
max_element = 7

# intiallize vector and populate from 0 to 7 of size 8 using std::iota
vec = pyzpk.integer_permutation(min_element,max_element)

assert vec.get(2) == 2
assert vec.get(1) == 1
assert vec.get(5) == 5
assert vec.get(7) == 7

# slice from a to b
vec1 = vec.slice(3,5)
assert vec1.get(5) == 5

# Permutating the vector
vec.set(0,7)
vec.set(1,4)
vec.set(2,3)
vec.set(3,0)
vec.set(4,5)
vec.set(5,1)
vec.set(6,2)
vec.set(7,6)

assert vec.get(2) == 3
assert vec.get(1) == 4
assert vec.get(5) == 1
assert vec.get(7) == 6

# .size()
assert vec.size() == 8

# Check is_valid permute
assert vec.is_valid() == True

# Random shuffle elements of vector
vec.random_shuffle()
assert vec.is_valid() == True

# Finding next permute
vec.next_permutation()
assert vec.is_valid() == True

# Finding next permute
vec2 = vec.inverse()
assert vec2.is_valid() == True

# set a number above max_element for idx 5
vec.set(5,10)
# Check is_valid permute
assert vec.is_valid() == False