class Node():

    def __init__(self, value=None, next_node=None):
        self.value = value
        self.next_node = next_node

# Add elements to linkedlist in sorted order.
class SortedList():
    def __init__(self):
        self.head = None

    def insert(self, value):
        new_node = Node(value)
        if self.head is None:
            self.head = new_node
            return

        if self.head.value > value:
            new_node.next_node = self.head

            # Assign new head.
            self.head = new_node
            return

        # Initialize iteration with head.
        current_node = self.head

        while current_node.next_node is not None or current_node.next_node.value <= value:
            current_node = current_node.next_node

        # Rewiring
        new_node.next_node = current_node.next_node
        current_node.next_node = new_node


# Function to get reflection of clock.
def get_reflection(hour : int, minute: int) :
    if minute == 0:
        minute_prime = minute
        hour_prime = 12 - hour
    else:
        minute_prime = 60 - minute
        hour_prime = 11 - hour

    if hour_prime <= 0:
        hour_prime = 12 + hour_prime

    return (hour_prime, minute_prime)


"""
1.
4:55 -> 7: 05

2.
2: 45 -> 9 and 10 -> 9 15

9:15 -> 2: 45


"""