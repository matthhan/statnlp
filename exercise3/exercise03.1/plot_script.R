
res <- read.csv("result.csv")
library(ggplot2)
library(reshape2)
molten <- melt(res,id.vars = "vocabulary_size")
ggplot(molten,aes(vocabulary_size,value,shape=variable,linetype=variable)) + geom_line() + ylab("") +geom_point() + theme_light()
res_smoothed <- read.csv("result_smoothed.csv")
ggplot(res_smoothed,aes(vocabulary_size,classifier_accuracy)) +geom_line() +geom_point() + theme_light()
