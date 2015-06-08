mydata <- read.table("custRating.csv",sep=",",header = F, stringsAsFactors = T)
prop.table(table(mydata[,3]))
summary(mydata[,3])
library("recommenderlab")
library(reshape)
data <- cast(mydata,V1~V2,value="V3")
#data[is.na(data)] <- 0
tm.useritem <- data[,-1]
class(tm.useritem) <-"data.frame"
tm.useritem <- as.matrix(tm.useritem)
tm.ratingMatrix <- as(tm.useritem,"realRatingMatrix")
tm.ratingMatrix
colnames(tm.ratingMatrix) <- paste("M",1:2556,set="")


model.eval <- evaluationScheme(tm.ratingMatrix[1:741], method = "split",train = 0.9, given = 2, goodRating = 3)
model.random <- Recommender(getData(model.eval, "train"), method = "RANDOM")
model.ubcf <- Recommender(getData(model.eval, "train"), method = "UBCF")
#model.ibcf <- Recommender(getData(model.eval, "train"), method = "IBCF")
predict.random <- predict(model.random, getData(model.eval, "known"), type = "ratings")
predict.ubcf <- predict(model.ubcf, getData(model.eval, "known"), type = "ratings")
#predict.ibcf <- predict(model.ibcf, getData(model.eval, "known"), type = "ratings")
error <- rbind(calcPredictionError(predict.random, getData(model.eval, "unknown")),calcPredictionError(predict.ubcf, getData(model.eval, "unknown")),calcPredictionError(predict.ibcf, getData(model.eval, "unknown")))
rownames(error) <- c("RANDOM", "UBCF", "IBCF")
error
summary(mydata[,3])
gc()
