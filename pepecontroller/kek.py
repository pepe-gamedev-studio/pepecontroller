import sqlite3
import gspread

# con = sqlite3.connect(database='pepe.sqlite3')
# gc = gspread.service_account(filename="gcp.json")

# cursor = con.cursor()
# # cursor.execute("SELECT * FROM user")
# # user = cursor.fetchall()

# cursor.execute("SELECT * FROM movie")
# movie = cursor.fetchall()

# # cursor.execute("SELECT * FROM movieVotes")
# # movieVotes = cursor.fetchall()
# con.close()

# print(movie)

# wks = gc.open("Table").worksheet("Movies")
# wks.update("A2", movie)

def push_to_gsheet (dbfile="pepe.sqlite3", dbtable="movie", gcpsettings="gcp.json", sheet="Table", worksheet="Movies"):
    con = sqlite3.connect(database=dbfile)
    gc = gspread.service_account(filename=gcpsettings)
    cursor = con.cursor()
    cursor.execute(f"SELECT * FROM {dbtable}")
    fetch = cursor.fetchall()
    con.close()
    wks = gc.open(sheet).worksheet(worksheet)
    wks.update("A2", fetch)
