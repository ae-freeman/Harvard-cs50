from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    stringA = a.splitlines()
    stringB = b.splitlines()

    similarLines =[]

    for i in range(len(stringA)):
        for j in range(len(stringB)):
            if stringA[i] == stringB[j]:
              similarLines.append(stringA[i])

    return set(similarLines)


def sentences(a, b):
    """Return sentences in both a and b"""

    stringA = sent_tokenize(a)
    stringB = sent_tokenize(b)

    identicalSentences =[]

    for i in range(len(stringA)):
        for j in range(len(stringB)):
            if stringA[i] == stringB[j]:
                identicalSentences.append(stringA[i])

    return set(identicalSentences)

def createSubstrings(str, n):
    substringsList = []

    for i in range(len(str) - n + 1):
        substringsList.append(str[i:i + n])

    return substringsList

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    alist = (createSubstrings(a, n))
    blist = (createSubstrings(b, n))

    identicalSubstrings = []

    for i in range(len(alist)):
        for j in range(len(blist)):
            if alist[i] == blist[j]:
              identicalSubstrings.append(alist[i])

    # return alist & blist
    return set(identicalSubstrings)








