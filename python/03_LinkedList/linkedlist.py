class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

    def __str__(self):
        return "{}".format(self.data)

class LinkedList:
    def __init__(self):
        self.size = 0
        self.head = None

    def add(self, data):
        if not self.head:
            self.head = Node(data)
        else:
            nd = self.head
            while nd.next:
                nd = nd.next
            nd.next = Node(data)

        self.size += 1

    def clear(self):
        self.head = None
        self.size = 0

    def contains(self, element):
        if self.size == 0:
            return False

        nd = self.head

        while nd:
            if nd.data == element:
                return True
            nd = nd.next

        return False

    def get(self, index):
        if index <0 or index >= self.size:
            return None

        ctr = 0
        nd = self.head

        while ctr != index:
            nd = nd.next
            ctr += 1
        return nd.data

    def index_of(self, element):
        if not self.contains(element):
            return -1

        ctr = 0
        nd = self.head

        while nd:
            if nd.data == element:
                return ctr
            nd = nd.next
            ctr += 1

        return -1

    def is_empty(self):
        return self.size == 0

    def remove_index(self, index):
        """removes and returns element at given index"""
        if index < 0 or index >= self.size:
            return None

        if index == 0:
            temp = self.head
            self.head = self.head.next
            self.size -= 1
            return temp

        ctr = 0
        nd = self.head

        while ctr != (index-1):
            nd = nd.next
            ctr += 1

        temp = nd.next
        nd.next = nd.next.next
        self.size -= 1
        return temp

    def remove_element(self, element):
        return self.remove_index(self.index_of(element))
    
    def __len__(self):
        return self.size

    def to_list(self):
        list = []
        nd = self.head

        while nd:
            list.append(nd.data)
            nd = nd.next
        
        return list


    def __str__(self):
        full_str = "size: {}\n".format(self.size)
        nd = self.head
        count = 0
        while nd:
            full_str += "{}: {}\n".format(count, nd.__str__())
            nd = nd.next
            count += 1
        return full_str

if __name__ == "__main__":
    ls = LinkedList()

    ls.add("red")
    ls.add("green")
    ls.add("blue")

    print(ls)

    print("contains blue:", ls.contains("blue"))
    print("contains bleu:", ls.contains("bleu"))

    print("get element at index 2:", ls.get(2))
    print("get element at index 3:", ls.get(3))

    print("get index of red:", ls.index_of("red"))
    print("get index of grey:", ls.index_of("grey"))

    print("is the list empty?", ls.is_empty())
    print("size:", len(ls))

    print("remove element at index 1:", ls.remove_index(1))

    print(ls)

    print(ls.to_list())
