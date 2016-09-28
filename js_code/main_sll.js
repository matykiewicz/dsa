
function Node ( data ) {
  this.data = data;
  this.next = null;
}

function SinglyList ( )  {
  this._length = 0;
  this.head = null;
}

SinglyList.prototype.add = function(value) {
  var node = new Node(value),
      currentNode = this.head;

  // 1st use-case: an empty list 
  if (!currentNode) {
    this.head = node;
    this._length++;

    return node;
  }

  // 2nd use-case: a non-empty list
  while (currentNode.next) {
    currentNode = currentNode.next;
  }

  currentNode.next = node;

  this._length++;

  return node;
};

var sl = new SinglyList();
sl.add(11);
sl.add(22);


console.log("ffff"+sl.head.data+sl.head.next.data);


