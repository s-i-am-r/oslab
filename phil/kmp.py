def pat(s):
    arr=[0 for i in s]
    #len_=0
    for i in range(1,len(s)):
        len_=arr[i-1]
        while len_ != 0:
            if s[i]!=s[len_]:
                len_=arr[len_-1]
                continue
            arr[i]=len_+1
            break
        if len_ ==0 and s[0]==s[i] :
            arr[i]=1
    return arr

        
def match(s,patt):
    lps=pat(patt)
    i=0
    j=0
    k=0
    while i<len(s):
        if s[k]==patt[j]:
            k+=1
            j+=1
            if j==len(patt):
                return i
        else:
            i+=1
            j=lps[j-1] if j>0 else 0
    return -1

print(match("xbbna","bbna"))
            
            
    

