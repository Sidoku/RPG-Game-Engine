from tkinter import *
from PIL import ImageTk, Image
import mygameengine
import random
from tkinter import messagebox
from PIL import ImageTk, Image





def main():

    root = Tk()
    root.title("Boston-Mix")
    root.geometry("480x500") # backup

    # root.geometry("260x400")




    dungeonFrame = LabelFrame(root, text = "Dungeons", width = 240, height = 400) # dungeons
    # addFrame = LabelFrame(root, text = "Add", width = 240, height = 160)
    # deleteFrame = LabelFrame(root, text = "Delete", width = 240, height = 140)
    themeFrame = LabelFrame(root,text = "Theme", width = 210, height = 400)
    # editFrame = LabelFrame(root, text = "Edit", width = 210, height = 200)

    dungeonFrame.place(x = 10, y = 10)
    # addFrame.place(x = 10, y = 380)
    # deleteFrame.place(x = 10, y = 550)
    themeFrame.place(x = 260, y = 10)
    # editFrame.place(x = 260, y = 420)
    # tile1img = ImageTk.PhotoImage(Image.open("./assets/images/tiles/Theme1/1/1E.bmp"))
    # tile1label =Label(image = tile1img).place(x = 10, y = 10)


    # Dungeon panel

    tileRow = Label(dungeonFrame, text = "Number of Rows : ")
    tileCol = Label(dungeonFrame, text = "Number of Cols : ")
    rowFill = Entry(dungeonFrame, width = 5, textvariable = IntVar)
    colFill = Entry(dungeonFrame, width = 5)
    interconnectivity = Label(dungeonFrame, text = "Interconnectivity : ")
    interconnectivityFill = Entry(dungeonFrame, width = 5)
    treasurePercentage = Label(dungeonFrame, text = "Treasure % : ")
    treasurePercentageFill = Entry(dungeonFrame, width = 5)
    monsterCount = Label(dungeonFrame, text = "Monster Count : ")
    monsterCountFill = Entry(dungeonFrame, width = 5)
    playName = Label(dungeonFrame, text = "Player Name : ")
    playNameFill = Entry(dungeonFrame, width = 5)
    wrappingVar = IntVar()
    wrapping = Label(dungeonFrame, text = "Wrapping")
    wrappingFill = Checkbutton(dungeonFrame,variable = wrappingVar, onvalue = 1, offvalue = 0)
    customizeLevel  = Label(dungeonFrame, text = "Customize Level")


    # TODO: the order(index) in this dungeonDataList row,col,interconnectivity,wrap,treasure,monster,name,tile,player,monster
    # TODO fog has not been added yet, if you want to add, please add after name  -Yikan
    level = []
    dungeonDataList = []



    # Add panel

    # addPanelRowLabel = Label(addFrame, text = "Row No.")
    # addPanelColLabel = Label(addFrame, text = "Col No.")
    # addPanelMonsterLabel = Label(addFrame, text = "Monster : ")
    # addPanelTreasureLabel = Label(addFrame, text = "Treasure : ")
    # addPanelArrowsLabel = Label(addFrame, text = "Arrows : ")
    # addPanelMonsterRowFill = Entry(addFrame, width = 5)
    # addPanelMonsterColFill = Entry(addFrame, width = 5)
    # addPanelTreasureRowFill = Entry(addFrame, width = 5)
    # addPanelTreasureColFill = Entry(addFrame, width = 5)
    # addPanelArrowsRowFill = Entry(addFrame, width = 5)
    # addPanelArrowsColFill = Entry(addFrame, width = 5)

    #TODO created an addPanelDataList for data storing, please follow the order(index) monster row, monster col, treasure row, treasure col, arrows row, arrows col
    addPanelDataList = []

    # Delete panel
    # deletePanelRowLabel = Label(deleteFrame, text = "Row No.")
    # deletePanelColLabel = Label(deleteFrame, text = "Col No.")
    # deletePanelMonsterLabel = Label(deleteFrame, text = "Monster : ")
    # deletePanelTreasureLabel = Label(deleteFrame, text = "Treasure : ")
    # deletePanelArrowsLabel = Label(deleteFrame, text = "Arrows : ")
    # deletePanelMonsterRowFill = Entry(deleteFrame, width = 5)
    # deletePanelMonsterColFill = Entry(deleteFrame, width = 5)
    # deletePanelTreasureRowFill = Entry(deleteFrame, width = 5)
    # deletePanelTreasureColFill = Entry(deleteFrame, width = 5)
    # deletePanelArrowsRowFill = Entry(deleteFrame, width = 5)
    # deletePanelArrowsColFill = Entry(deleteFrame, width = 5)

    #TODO created a deletePanelDataList for data storing, please follow the order(index) monster row, monster col, treasure row, treasure col, arrows row, arrows col
    deletePanelDataList = []


    # Theme panel
    themePanelTileLabel = Label(themeFrame, text = "Select Tile")
    themePanelPlayerLabel = Label(themeFrame, text = "Select Player")
    themePanelMonsterLabel = Label(themeFrame, text = "Select Monster")
    themePanelSelectDiceLabel = Label(themeFrame, text = "Select Dice")

    # TODO: need pictures for tile, player, monster, and dice for user to select. if i wont be able to do it, you will use library called PIL
    # TODO: simply from PIL import ImageTk, Image
    # TODO: myImage = ImageTk.PhotoImage(Image.open("path to image.png"))
    # TODO: my_image_label = Label(image = myImage)
    # TODO: my_image_label.place(x = ? , y = ? )
    # TODO: you then can add radio button https://www.youtube.com/watch?v=YXPyB4XeYLA&t=8893s&ab_channel=freeCodeCamp.org @ 2:09:00 will help you alot  -Yikan

    themePanelDataList = []

    #  Edit panel
    # editPanelRowLabel = Label(editFrame, text = "Row No.")
    # editPanelColLabel = Label(editFrame, text = "Col No.")
    # editPanelStartCaveLabel = Label(editFrame, text = "Start Cave : ")
    # editPanelEndCaveLabel = Label(editFrame, text = "End Cave : ")
    # editPanelPlayerLocationLabel = Label(editFrame, text = "Player Loc. : ")
    # editPanelStartCaveRowFill = Entry(editFrame, width = 5)
    # editPanelStartCaveColFill = Entry(editFrame, width = 5)
    # editPanelEndCaveRowFill = Entry(editFrame, width = 5)
    # editPanelEndCaveColFill = Entry(editFrame, width = 5)
    # editPanelPlayerLocationRowFill = Entry(editFrame, width = 5)
    # editPanelPlayerLocationColFill = Entry(editFrame, width = 5)

    #TODO created an editPanelDataList for data storing, please follow the order(index) start cave row, start cave col, end cave row, end cave col, player location row, player location col
    editPanelDataList = []

    # Theme Panel
    chooseTileLable = Label(themeFrame, text = "Choose Tile : ")
    choosePlayerLable = Label(themeFrame, text = "Choose Player : ")
    chooseMonsterLable = Label(themeFrame, text = "Choose Monster : ")


    # tile selection
    tilePicked = StringVar()
    tilePicked.set("Theme1")
    tile1button = Radiobutton(variable = tilePicked, value = "Theme1")
    tile1button.place(x = 265, y = 70)
    tile2button = Radiobutton(variable = tilePicked, value = "Theme2")
    tile2button.place(x = 360, y = 70)
    tileimg1 = Image.open("./assets/images/tiles/Theme1/1/1E.bmp")
    tile1img = ImageTk.PhotoImage(tileimg1)
    tile1label =Label(image = tile1img).place(x = 290, y = 55)
    tile2img = ImageTk.PhotoImage(Image.open("./assets/images/tiles/Theme2/1/1N.bmp"))
    tile2label =Label(image = tile2img).place(x = 385, y = 55)

    # player selection
    playerPicked = StringVar()
    playerPicked.set("Knight")
    player1button = Radiobutton(variable = playerPicked, value = "Knight")
    player1button.place(x = 265, y = 180)
    player2button = Radiobutton( variable = playerPicked, value = "Mage")
    player2button.place(x = 360, y = 180)
    playerimg1 = Image.open("./assets/images/Player/knight.bmp")
    player1img = ImageTk.PhotoImage(playerimg1)
    player1label =Label(image = player1img).place(x = 290, y = 160)
    player2img = ImageTk.PhotoImage(Image.open("./assets/images/Player/mage.bmp"))
    player2label =Label(image = player2img).place(x = 385, y = 160)


    # monster selection
    monsterPicked = StringVar()
    monsterPicked.set("ORK1")
    monster1button = Radiobutton(variable = monsterPicked, value = "ORK1")
    monster1button.place(x = 265, y = 285)
    monster2button = Radiobutton(variable = monsterPicked, value = "ORK2")
    monster2button.place(x = 360, y = 285)
    monsterimg1 = Image.open("./assets/images/Monster/ORK1.bmp")
    monster1img = ImageTk.PhotoImage(monsterimg1)
    monster1label =Label(image = monster1img).place(x = 290, y = 270)
    monster2img = ImageTk.PhotoImage(Image.open("./assets/images/Monster/ORK2.bmp"))
    monster2label =Label(image = monster2img).place(x = 385, y = 270)



    def dataCollector():
        dungeonDataList.clear()
        print("previous settings cleared")
        try:
            dungeonDataList.append(int(rowFill.get()))
        except:
            messagebox.showerror("Error", "Please enter a value for row").pack()
        if int(rowFill.get()) < 0:
            messagebox.showerror("Error", "Please provide a valid value for row").pack()
        if int(rowFill.get()) > 17:
            messagebox.showerror("Error", "Please provide a smaller value for row").pack()
        try:
            dungeonDataList.append(int(colFill.get()))
        except:
            messagebox.showerror("Error", "Please enter a value for column").pack()
        if int(colFill.get()) < 0:
            messagebox.showerror("Error", "Please provide a valid value for column").pack()

        if int(rowFill.get()) * int(colFill.get()) < 10:
            messagebox.showerror("Error", "Please provide larger values for row and column").pack()

        if int(colFill.get()) > 17:
            messagebox.showerror("Error", "Please provide a smaller value for column").pack()
        try:
            dungeonDataList.append(int(interconnectivityFill.get()))
        except:
            messagebox.showerror("Error", "Please enter a value for interconnectivity").pack()
        if int(interconnectivityFill.get()) < 0:
            messagebox.showerror("Error", "Please provide a larger value for interconnectivity").pack()

        if wrappingVar.get() == 1:
            dungeonDataList.append(True)
        else:
            dungeonDataList.append(False)

        try:
            dungeonDataList.append(int(treasurePercentageFill.get()))
        except:
            messagebox.showerror("Error", "Please enter a value for treasure percentage").pack()
        if int(treasurePercentageFill.get()) <= 0 or int(treasurePercentageFill.get()) > 100:
            messagebox.showerror("Error", "Invalid treasure percentage").pack()
        try:
            dungeonDataList.append(int(monsterCountFill.get()))
        except:
            messagebox.showerror("Error", "Please enter a value for monster count").pack()
        if int(monsterCountFill.get()) >= int(rowFill.get()) * int(colFill.get()) - 1 or int(monsterCountFill.get()) <= 0:
            messagebox.showerror("Error", "Invalid monster count").pack()
        try:
            dungeonDataList.append(str(playNameFill.get()))
        except:
            messagebox.showerror("Error", "Please enter a name for player").pack()

        if str(playNameFill.get()) == "" or str(playNameFill.get()) == " ":
            messagebox.showerror("Error", "Please enter a name for player").pack()
            return
        print(dungeonDataList)


        # row col interconnectivity wrap treasure monster name
        if len(dungeonDataList) == 0:
            messagebox.showerror("Error", "Please modify the game setting first or submit settings").pack()


        # if str(tilePicked.get()) != "Theme1" or str(tilePicked.get()) != "Theme2":
        #     messagebox.showerror("Error", "Please select a tile").pack()
        # if playerPicked.get() != "Knight" or playerPicked.get() != "Mage":
        #     messagebox.showerror("Error", "Please select a player").pack()
        # if monsterPicked.get() != "ORK1" or monsterPicked.get() != "ORK2":
        #     messagebox.showerror("Error", "Please select a monster").pack()
        #


        if clicked.get() == 1:
            print('one')
            level.append(dungeonDataList)
        elif clicked.get() == 2:
            print("two")
            level.append(dungeonDataList)
        else:
            print("three")
            level.append(dungeonDataList)

        print(len(level))
        print(level)


    def getPixel (row, col) :
        if row < 7 and col < 7:
            pix = 128
        elif row > 13 or col > 13:
            pix = 54
        elif row > 11 or col > 11:
            pix = 72
        else:
            pix = 100
        return pix

    def runGameLoop(level):
        # // [7, 7, 5, True, 25, 5, 'sanj']
        #Running all levels if player wins each level
        game_running = True
        level_no = 0
        print("Monster : ", monsterPicked.get())
        print("Player : ", playerPicked.get())
        print("Tile : ", tilePicked.get())
        ##TODO fix why the game window doesnt quit
        while game_running and level_no < len(level):
            pix = getPixel(level[level_no][0],level[level_no][1])
            print("Pix :", pix)
            print("Level " ,level[level_no][0])
            game = mygameengine.GameModel(level[level_no][0],  level[level_no][1],
                                          level[level_no][2], level[level_no][3],
                                          level[level_no][4],  level[level_no][5],
                                          level[level_no][6], pix)
            engine = mygameengine.Engine(game)
            print(tilePicked.get())
            print(playerPicked.get())
            engine.InitializeGraphicsSubSystem(level[level_no][0]*pix + 4 * pix, level[level_no][1]*pix, tilePicked.get(), playerPicked.get(), monsterPicked.get())
            engine.Start()
            game_running = engine.MainGameLoop()
            engine.Shutdown()
            level = level + 1

        # game = mygameengine.GameModel(dungeonDataList[0],  dungeonDataList[1], dungeonDataList[2], dungeonDataList[3], dungeonDataList[4],  dungeonDataList[5], dungeonDataList[6],pix)
        # engine = mygameengine.Engine(game)
        # engine.InitializeGraphicsSubSystem(row*pix + 4 * pix, col*pix)
        # engine.Start()
        # engine.MainGameLoop()
        # engine.Shutdown()

    #for commmit purpose
    #for commit purpose
    def runRandomGame():
        random_level_number = 1;
        l = 0
        random_level = []
        # row,col,interconnectivity,wrap,treasure,monster,name
        while(len(random_level) <= 3) :
            rand_level = []
            rand_level.insert(0,random.randint(5,9))
            rand_level.insert(1,random.randint(5,9))
            rand_level.insert(2,random.randint(1,5))
            wrap = random.randint(0,1)
            if(wrap == 0) :
                rand_level.insert(3,True)
            else :
                rand_level.insert(3,False)
            rand_level.insert(4,random.randint(15,70))
            rand_level.insert(5,random.randint(4,10))
            rand_level.insert(6,"Player1")
            random_level.insert(l,rand_level)
            l+=1
        level_no =1
        game_running = True
        while game_running and level_no < len(random_level):
            pix = getPixel(random_level[level_no][0],random_level[level_no][1])
            print("Pix :", pix)
            print("Level " ,random_level[level_no][0])
            game = mygameengine.GameModel(random_level[level_no][0],  random_level[level_no][1],
                                          random_level[level_no][2], random_level[level_no][3],
                                          random_level[level_no][4],  random_level[level_no][5],
                                          random_level[level_no][6], pix)
            engine = mygameengine.Engine(game)
            engine.InitializeGraphicsSubSystem(random_level[level_no][0]*pix + 4 * pix, random_level[level_no][1]*pix, "Theme1", "Knight", "ORK1")
            engine.Start()
            game_running = engine.MainGameLoop()
            engine.Shutdown()
            level = level + 1



    startGame = Button(root, text = "Start Your Game", command = lambda:runGameLoop(level))
    startRandomGame = Button(root, text = "Start Random Game", command = runRandomGame)
    startGame.pack(side = BOTTOM, pady =5)
    startRandomGame.pack(side = BOTTOM)
    clicked = IntVar()
    clicked.set(1)
    customizeLevelMenu = OptionMenu(dungeonFrame, clicked, 1, 2, 3)



    levelSubmit = Button(root, text = "submit", command = dataCollector)



    # DUNGEON PANEL SETTINGS
    # TODO fog data is not fetch yet, let Yikan know pls
    tileRow.place(x = 10, y = 10)
    rowFill.place(x = 130, y = 10)
    tileCol.place(x = 10, y = 50)
    colFill.place(x = 130, y = 50)
    interconnectivity.place(x = 10, y = 90)
    interconnectivityFill.place(x = 130, y = 90)
    treasurePercentage.place(x = 10, y = 130)
    treasurePercentageFill.place(x = 130, y = 130)
    monsterCount.place(x = 10, y = 170)
    monsterCountFill.place(x = 130, y = 170)
    playName.place(x = 10, y = 210)
    playNameFill.place(x = 130, y = 210)
    wrapping.place(x = 10, y = 250)
    wrappingFill.place(x = 130, y = 250)
    customizeLevel.place(x = 10, y = 290)
    customizeLevelMenu.place(x = 130, y = 290)
    levelSubmit.place(x = 90, y = 370)

    # THEME PANEL SETTINGS
    chooseTileLable.place(x = 0, y = 0)
    choosePlayerLable.place(x = 0, y = 105)
    chooseMonsterLable.place(x = 0, y = 210)





    # ADD PANEL SETTINGS
    # addPanelRowLabel.place(x = 100, y = 10)
    # addPanelColLabel.place(x = 160, y = 10)
    # addPanelMonsterLabel.place(x = 10, y = 40)
    # addPanelMonsterRowFill.place(x = 100, y = 40)
    # addPanelMonsterColFill.place(x = 160, y = 40)
    # addPanelTreasureLabel.place(x = 10, y = 70)
    # addPanelTreasureRowFill.place(x = 100, y = 70)
    # addPanelTreasureColFill.place(x = 160, y = 70)
    # addPanelArrowsLabel.place(x = 10, y = 100)
    # addPanelArrowsRowFill.place(x = 100, y = 100)
    # addPanelArrowsColFill.place(x = 160, y = 100)
    #
    # # DELETE PANEL SETTINGS
    # deletePanelRowLabel.place(x = 100, y = 0)
    # deletePanelColLabel.place(x = 160, y = 0)
    # deletePanelMonsterLabel.place(x = 10, y = 20)
    # deletePanelMonsterRowFill.place(x = 100, y = 20)
    # deletePanelMonsterColFill.place(x = 160, y = 20)
    # deletePanelTreasureLabel.place(x = 10, y = 50)
    # deletePanelTreasureRowFill.place(x = 100, y = 50)
    # deletePanelTreasureColFill.place(x = 160, y = 50)
    # deletePanelArrowsLabel.place(x = 10, y = 80)
    # deletePanelArrowsRowFill.place(x = 100, y = 80)
    # deletePanelArrowsColFill.place(x = 160, y = 80)
    #
    #
    # # EDIT PANEL SETTINGS
    # editPanelRowLabel.place(x = 85, y = 0)
    # editPanelColLabel.place(x = 145, y = 0)
    # editPanelStartCaveLabel.place(x = 0, y = 30)
    # editPanelEndCaveLabel.place(x = 0, y = 70)
    # editPanelPlayerLocationLabel.place(x = 0, y = 110)
    # editPanelStartCaveRowFill.place(x = 80, y = 30)
    # editPanelStartCaveColFill.place(x = 140, y = 30)
    # editPanelEndCaveRowFill.place(x = 80, y = 70)
    # editPanelEndCaveColFill.place(x = 140, y = 70)
    # editPanelPlayerLocationRowFill.place(x = 80, y = 110)
    # editPanelPlayerLocationColFill.place(x = 140, y = 110)






    root.mainloop()

















if __name__ == "__main__":
    main()




