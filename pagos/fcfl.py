
class frames():
    
    def __init__(self,n_fr) -> None:
        self.frame:list=[None for i in range(n_fr)]
        self.fcfl = []
        self.lru = []
        self.opt = []
        self.done=0
    def page_fcfl2(self,pages:list):
        done=0
        i=0
        while done<len(pages):
            if pages[done] not in self.frame:
                self.frame[i]=pages[done]
                i = (i+1)%len(self.frame)
            done+=1
            print(self.frame)
        
    def page_fcfl(self,pages:list):
        done=0
    
        while done<len(pages):
            if pages[done] not in self.frame:
                try :
                    ind = self.frame.index(None)
                    self.frame[ind]=pages[done]
                    self.fcfl.append(pages[done])
                except ValueError:
                    ind = self.frame.index(self.fcfl[0])
                    self.frame[ind]=pages[done]
                    self.fcfl =self.fcfl[1:]+[pages[done]]
            done+=1
            print(self.frame)
    def page_lru(self,pages:list):
        lru=[i for i in range(len(self.frame))]
        done=0
        while done<len(pages):
            if pages[done] not in self.frame:
                ind =lru[0]
                self.frame[ind]= pages[done]
                lru =lru[1:]+[ind]
            else:
                ind = self.frame.index(pages[done])
                indd = lru.index(ind)
                lru = lru[:indd]+lru[indd+1:]+[ind]
            done+=1
            print(f"{self.frame},{lru}")
    def page_opt(self,pages:list):
        def find_ch_gt_n(l:list,n:int):
            for i in l:
                if i >n:
                    return i
                
            return None
        nxt=[[] for i in range(5)]
        for x in range(len(pages)):
            nxt[pages[x]].append(x)
        done =0
        while done<len(pages):
            if pages[done] not in self.frame:
                if None in self.frame:
                    ind=self.frame.index(None)
                    self.frame[ind]=pages[done]
                else:  
                    gt=-1  
                    gti=-1
                    for i in range(len(self.frame)):
                        x = find_ch_gt_n(nxt[i],done)
                        if x==None:
                            self.frame[i]=pages[done]
                            gti=None
                            break
                        if gt < x:
                            gt=x
                            gti=i
                    if gti is not None:
                        self.frame[gti]=pages[done]
            done+=1
            print(self.frame)
                    
                
                
            
        
                
                
if __name__=='__main__':
    with open("input.txt","r") as myfile:
        txt = myfile.readline()
    
    pages = list(map(lambda x:int(x), txt.split(" ")))
    myframe = frames(3)
    print(pages)
    myframe.page_opt(pages)
    
                    
                
            