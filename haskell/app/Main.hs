
import Raylib.Core (
  initWindow,
  setTargetFPS,
  windowShouldClose,
  clearBackground,
  closeWindow,
  beginDrawing,
  endDrawing,
  getRandomValue,
  )
import Raylib.Types (Color)
import Raylib.Core.Text (
    drawText,
    )
import Raylib.Core.Shapes (
  drawCircle,
  )
import Raylib.Util.Colors

data Boule = Boule
  {  posX   :: Int
  ,  posY   :: Int
  ,  vitX   :: Int
  ,  vitY   :: Int
  ,  altVit :: Int
  ,  radius :: Int
  ,  color  :: Color
  ,  score  :: Int
  }

-- Couldn't import LoopWhile for some reason
while :: IO Bool -> (a -> IO a) -> a -> IO ()
while cond f context = do
  bool <- cond
  if bool
    then f context >>= while cond f
    else pure ()

drawBoule :: Boule -> IO()
drawBoule b = drawCircle posX' posY' radius' (color b)
  where posX'   = posX b
        posY'   = posY b
        radius' = fromIntegral $ radius b :: Float

createBoule :: Int -> Int -> Color -> Boule
createBoule x y c = Boule x y 1 0 0 5 c 0

checkCollision :: Boule -> Boule
checkCollision boule = checkY $ checkLeft $ checkRight boule
  where checkRight b | futX >= 1200 = b { vitX = -(vitX b) }
                     | otherwise = b
        checkLeft  b | futX <= 0 = b { vitX = -(vitX b), score = (score b)+1 }
                     | otherwise = b
        checkY     b | futY <= 0 = b { vitX = -(vitX b) }
                     | futY >= 200 = b { vitX = -(vitX b) }
                     | otherwise = b
        futX = (posX boule)+(vitX boule)*(altVit boule)
        futY = (posY boule)+(vitY boule)

changeAlt :: Int -> Boule -> Boule
changeAlt val b = b { altVit = val+score b }

move :: Boule -> Boule
move b = b { posX = posX b + vitX b * altVit b, posY = posY b + vitY b }


main :: IO ()
main = do
  window <- initWindow 1200 200 "Boulatro"
  setTargetFPS 60
  let boule1 = createBoule 10 150 green
  let boule2 = createBoule 10 160 yellow
  let boule3 = createBoule 10 170 red
  while (not <$> windowShouldClose) frame (boule1, boule2, boule3)
  closeWindow $ Just window
    where frame (b1, b2, b3) = do 
            beginDrawing
            clearBackground black
            drawText "Lap : " 1 0 20 white
            drawText (show $ score b1) 1 20 20 green
            drawText (show $ score b3) 1 60 20 red
            drawBoule b1
            drawBoule b3
            endDrawing
            altVit1 <- getRandomValue 0 9
            altVit2 <- getRandomValue 0 9
            altVit3 <- getRandomValue 0 9
            pure (
              move $ changeAlt altVit1 $ checkCollision b1,
              move $ changeAlt altVit2 $ checkCollision b2,
              move $ changeAlt altVit3 $ checkCollision b3)

