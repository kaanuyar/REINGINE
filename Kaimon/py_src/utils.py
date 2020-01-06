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
        
        net.load_state_dict(torch.load(path))

    else:
        print("DOSYA BULUNAMADI. AĞ RASTGELE AĞIRLIKLARLA BAŞLATILIYOR...")
        
    if training:
 
        return net.to(device),dqn_model.DQN(12, 360).to(device).load_state_dict(torch.load(path))
    
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
    done=state_dic["isGameOver"]
    player_min=player["playerMin"]
    player_max=player["playerMax"]
    target_min=target["targetMin"]
    target_max=target["targetMax"]
	
    result.append(player_min)
    result.append(player_max)
    result.append(target_min)
    result.append(target_max)
    result.append(done)
    
    return result


