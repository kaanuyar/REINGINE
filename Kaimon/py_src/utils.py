# -*- coding: utf-8 -*-
"""
Created on Tue Dec 24 04:01:36 2019

@author: mustafa
"""
import dqn_model
import os
import torch
def load_models(path,training=False,device="cpu"):
    
    net = dqn_model.DQN(12, 360)

    if os.path.exists(path):
        print("DOSYA BULUNDU. AĞ AĞIRLIKLARI DOSYADAN ÇEKİLİYOR...")
        
        net.load_state_dict(torch.load(path,map_location=torch.device("cpu")))

    else:
        print("DOSYA BULUNAMADI. AĞ RASTGELE AĞIRLIKLARLA BAŞLATILIYOR...")
        
    if training:
 
        return net.to(device),dqn_model.DQN(12, 360).to(device)
    
    return net.to(device)


def get_obs(state_dic):
    """
    Parameters
            state_dic: current state of agent coming from environment
    output:
            list of list of all objects' min and max coordinates
    """
    result=[]
    player=state_dic["player"]
    target=state_dic["target"]
    obs=state_dic["obstacle"]
    done=state_dic["isGameOver"]
    player_min=player["playerMin"]
    player_max=player["playerMax"]
    target_min=target["targetMin"]
    target_max=target["targetMax"]
    obs_min=obs["obstacleMin"]
    obs_max=obs["obstacleMax"]
    player_min=[player_min[0],player_min[2]]
    player_max=[player_max[0],player_max[2]]
    target_min=[target_min[0],target_min[2]]
    target_max=[target_max[0],target_max[2]]
    obs_min=[obs_min[0],obs_min[2]]
    obs_max=[obs_max[0],obs_max[2]]
    result.append(player_min)
    result.append(player_max)
    result.append(target_min)
    result.append(target_max)
    result.append(obs_min)
    result.append(obs_max)
    
    
    return result,done


