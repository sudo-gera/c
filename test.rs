


class Item(Generic[V]):
    def __init__(self: Item[V], v: Option[V]):
        self.newer: int = 0;
        self.older: int = 0;
        self.val: Option[V] = v;


fn main(){

}
