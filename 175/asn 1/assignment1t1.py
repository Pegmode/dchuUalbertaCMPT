#assignment 1-1
#Daniel Chu 1493371
from datetime import date
class Family():
    def __init__(self,phone_number,name,address):
        self.phone_number = phone_number
        self.name = name
        self.address = address
        self.payments = []
        self.dues = [] #dues refers to all the separate transactions the add on to fees
        self.fees = float(0) #fees refers to the total ammount due
        self.has_interest = False

    def add_payment(self,transaction):
        self.payments.append(transaction)
        self.fees -= transaction.amount

    def add_due(self,transaction):
        self.dues.append(transaction)
        self.fees += transaction.amount

 
    def get_attributes(self):
        return self.phone_number,self.name,self.address,self.fees, self.dues

class Transaction():
    def __init__(self,date,amount,phone_number,type):
        self.date = date
        self.amount = amount ##PAYMENT VALUES SHOULD BE STORED AS NEGATIVE!!!
        self.phone_number = phone_number
        self.type = type

    def get_amount(self):
        return self.amount

    def get_attributes(self):
        return self.date,self.amount,self.phone_number

class TabProgram():
    def __init__(self):
        self.dues_filepath = 'dues.txt'
        self.payments_filepath = 'payments.txt'
        self.families_filepath = 'families.txt'
        self.summary_fillepath = 'summary.txt'
        self.families_dict = {}
        self.interest_rate = 0.01 #1%
        self.run()

    def run(self):
        self.create_families()
        self.tally_payments()

        print('asdfjasjdhf')
        self.output_table()

    def read_files(self,file_path,separator,line_list):
        f = open(file_path,'r')
        file_read_buffer = f.readlines()
        f.close()
        for line in file_read_buffer:
            line_list.append(line.split(separator))

    def create_families(self):#create family objects and populate family list
        families_line_buffer = []
        self.read_files(self.families_filepath,',',families_line_buffer)
        for families in families_line_buffer:
            if len(families) == 3:#if there are 3 entires in line
                self.families_dict[families[0]] = Family(families[0],families[1],families[2])

    def tally_payments(self):
        dues_buffer = []
        self.read_files(self.dues_filepath,';',dues_buffer)
        transaction_buffer = self.create_transactions(dues_buffer,'dues')
        for transaction in transaction_buffer:
            for family in self.families_dict:
                if family == transaction.phone_number: #without int it totally bugs out
                    self.families_dict[family].add_due(transaction)

        payments_buffer = []
        self.read_files(self.payments_filepath,';',payments_buffer)
        transaction_buffer = self.create_transactions(payments_buffer,'dues')
        for transaction in transaction_buffer:
            for family in self.families_dict:
                if family == transaction.phone_number: #without int it totally bugs out
                    self.families_dict[family].add_payment(transaction)


    def create_transactions(self,transaction_list,type):
        return_buffer = []
        for transaction in transaction_list:
            return_buffer.append(Transaction(transaction[0],float(transaction[1]),transaction[2].replace('\n',''),type))
        return return_buffer

    def output_table(self):
        #f = open(self.summary_fillepath,'w')
        print('+--------------+------------------+--------+-----+\n| Phone Number | Name             | Due    | Int |\n+--------------+------------------+--------+-----+')
        #f.write('+--------------+------------------+--------+-----+\n| Phone Number | Name             | Due    | Int |\n+--------------+------------------+--------+-----+\n')

        for family in self.families_dict:
            #formatting table entry data
            #phone format
            phone_number = self.families_dict[family].phone_number#makes next line legibale
            formatted_phone_number = '({}) {} {}'.format(phone_number[0:3],phone_number[3:6],phone_number[6:10])
            if self.families_dict[family].fees > 500:
                self.families_dict[family].name = '**' + self.families_dict[family].name
            #interest calculation
            interest = 0
            if self.families_dict[family].fees > 100:
                interest = self.families_dict[family].fees * self.interest_rate
                self.families_dict[family].fees += interest


            print("|{0}|{1}|${2:.2f}|${3:.2f}|{4}".format(formatted_phone_number,self.families_dict[family].name.ljust(18),self.families_dict[family].fees,interest,self.format_payments(self.families_dict[family])))

        print("+--------------+------------------+--------+-----+")

    def format_payments(self,family):
        payment_string = ''
        if len(family.payments) > 0:
            total = 0
            for payments in family.payments:
                payment_string += ' {0} (${1:.2f});'.format(payments.date,payments.amount)
            payment_string = str(total) + payment_string

        return payment_string


    def print_and_writefile(self,file,message):
        print(message)
        file.write(message + 'n')

    def DBg(self):
        for i in self.families_dict:
            print(i)
def test():
	pass


def main():
    program = TabProgram()
main()
