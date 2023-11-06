class Object(dict): # allow a.name instead of a['name']
    def __init__(self,*a,**s):
        super().__init__(*a,**s)
        self.__dict__=self


