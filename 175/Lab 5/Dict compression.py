#Single line populating a dict

x = ['asdf:3124','asdasdf:11223','asdf:123','asdfsdf:2234235']

l = {i.split(':')[0]:i.split(':')[1] for i in x}

#must have brackets around for, thing before for is key or index or thing based on item (i)
