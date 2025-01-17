"""
This program asks the user for minimum and maximum song tempo.
Based on the input, filtered data from csv file will be displayed.
"""

from csv import DictReader


def main():
    min_tempo = int(input("Minimum tempo: "))
    max_tempo = int(input("Maximum tempo: "))

    playlist = []
    filename = "2018_top100.csv"
    # Read songs from 2018_top100.csv into playlist
    with open(filename) as file:
        file_reader = DictReader(file)
        for song in file_reader:
            if float(song["tempo"]) > min_tempo and float(song["tempo"]) < max_tempo:
                                                  playlist.append(song["name"])

    # Print song titles from playlist
    for song in playlist:
        print(song)

if __name__ == "__main__":
    main()
